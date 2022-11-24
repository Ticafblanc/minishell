/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblanco <tblanco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/11/23 22:16:58 by tblanco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	manage_error_execve(t_cmd *cmd)
{
	int	stat;

	stat = perror_minishell(NCMD, cmd->cmd[0]);
	free_null(cmd->path);
	free_next_cmds(cmd);
	exit(stat);
}

static void	child_process(t_cmd *cmd, char **envp)
{
	if (cmd->ctrl_op == PIPE || cmd->flag & F_BRACE)
	{
		cmd->cmd[2] = ft_rev_split((const char **)cmd->cmd, 32);
		cmd->cmd[0] = ft_strdup("minishell");
		cmd->cmd[1] = ft_strdup("-c");
		cmd->cmd[3] = NULL;
	}
	else
		manage_args(cmd, envp);
	if (*cmd->cmd[0] == '/' || *cmd->cmd[0] == '.' || *cmd->cmd[0] == '~')
		cmd->path = ft_strdup(cmd->cmd[0]);
	else
		cmd->path = find_path_child(cmd->cmd[0], envp);
	execve(cmd->path, cmd->cmd, envp);
	manage_error_execve(cmd);
}

void	exec_cmd(t_cmd *cmd, char **envp, int options)
{
	signal(SIGINT, handle_exe);
	signal(SIGQUIT, handle_exe);
	if (*cmd->cmd)
	{
		cmd->pid = fork();
		if (cmd->pid == -1)
			exit(perror_minishell(errno, "Fork child_process"));
		if (!cmd->pid)
		{
			if (cmd->ctrl_op == PIPE && cmd->outfile == STDOUT_FILENO)
				switch_streams(cmd->fd[0], cmd->fd[1], STDOUT_FILENO);
			dup_file(cmd);
			child_process(cmd, envp);
		}
		waitpid (cmd->pid, get_status(), options);
	}
	if (cmd->infile != STDIN_FILENO)
		close(cmd->infile);
	if (cmd->outfile != STDOUT_FILENO)
		close(cmd->outfile);
}

static void	pipe_loop(t_cmd **cmd, char ***envp)
{
	while ((*cmd)->ctrl_op == PIPE)
	{
		if (pipe((*cmd)->fd) == -1)
			exit(perror_minishell(errno, "Pipe"));
		if (!exec_builtins(*cmd, envp, CHILD))
			exec_cmd(*cmd, *envp, WNOHANG);
		close((*cmd)->fd[1]);
		if ((*cmd)->next->infile == STDIN_FILENO)
			(*cmd)->next->infile = (*cmd)->fd[0];
		(*cmd) = (*cmd)->next;
	}
}

int	exec_pipe(t_cmd *cmd, char **envp)
{
	pid_t	pid;
	t_cmd	*tmp;

	if (cmd->ctrl_op != PIPE)
		return (0);
	pid = fork();
	if (pid == -1)
		exit(perror_minishell(errno, "Fork child_process"));
	if (!pid)
	{
		tmp = cmd;
		pipe_loop(&cmd, &envp);
		if (!exec_builtins(cmd, &envp, CHILD))
			exec_cmd(cmd, envp, 0);
		wait_next_cmds(tmp);
		exit(*get_status());
	}
	waitpid(pid, get_status(), 0);
	close_pipe_fd(cmd);
	return (1);
}
