/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/11/02 19:21:04 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	child_process(t_cmd *cmd, char **envp)
{
	int	stat;

	if (cmd->ctrl_op == PIPE || cmd->ctrl_op == BRACE)
	{
		if (cmd->ctrl_op == PIPE)
			cmd->cmd[2] = ft_rev_split((const char **)cmd->cmd, 32);
		else
			cmd->cmd[2] = cmd->cmd[0];
		cmd->cmd[0] = ft_strdup("minishell");
		cmd->cmd[1] = ft_strdup("-c");
		cmd->cmd[3] = NULL;
	}
	cmd->cmd = manage_var(cmd, envp);
	manage_wildcard(cmd);
	if (*cmd->cmd[0] == '/' || *cmd->cmd[0] == '.' || *cmd->cmd[0] == '~')
		cmd->path = cmd->cmd[0];
	else
		cmd->path = find_path(cmd->cmd[0], envp);
	execve(cmd->path, cmd->cmd, envp);
	stat = perror_minishell(NCMD, cmd->cmd[0]);
	free_cmd(cmd);
	exit(stat);
}

void	exec_cmd(t_cmd *cmd, char **envp, int options)
{
	cmd->pid = fork();
	if (cmd->pid == -1)
		exit(perror_minishell(errno, "Fork child_process"));
	if (!cmd->pid)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		if (cmd->ctrl_op == PIPE && cmd->outfile == STDOUT_FILENO)
			switch_streams(cmd->fd[STDIN_FILENO], cmd->fd[STDOUT_FILENO], STDOUT_FILENO);
		dup_file(cmd);
		child_process(cmd, envp);
	}
	if(cmd->ctrl_op == PIPE)
		switch_streams(cmd->fd[STDOUT_FILENO], cmd->fd[STDIN_FILENO], STDIN_FILENO);
	waitpid(cmd->pid, get_status(), options);
}

static void	pipe_loop(t_cmd **cmd, char ***envp)
{
	while ((*cmd)->ctrl_op == PIPE)
	{
		if (pipe((*cmd)->fd) == -1)
				exit(perror_minishell(errno, "Pipe"));
		if (!exec_builtins(*cmd, envp, CHILD))
			exec_cmd(*cmd, *envp, WNOHANG);
		*cmd = (*cmd)->next;
	}
}


int	exec_pipe(t_cmd *cmd, char **envp)
{
	t_cmd	*t_cmd;
	pid_t 	pid;

	if (cmd->ctrl_op != PIPE)
		return (0);
	pid = fork();
	if (pid == -1)
		exit(perror_minishell(errno, "Fork child_process"));
	if(!pid)
	{
		t_cmd = cmd;
		pipe_loop(&cmd, &envp);
		if (!exec_builtins(cmd, &envp, CHILD))
			exec_cmd(cmd, envp, 0);
		wait_cmd(t_cmd, PIPE);
		exit(*get_status());
	}
	waitpid(pid, get_status(), 0);
	return (1);
}
