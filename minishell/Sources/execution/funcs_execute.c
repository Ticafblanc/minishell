/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/11/13 12:11:38 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	manage_args(t_cmd *cmd, char **envp);

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
		cmd->malloced |= 0x1;
	}
	manage_args(cmd, envp);
	if (*cmd->cmd[0] == '/' || *cmd->cmd[0] == '.' || *cmd->cmd[0] == '~')
		cmd->path = cmd->cmd[0];
	else
	{
		cmd->path = find_path(cmd->cmd[0], envp);
		cmd->malloced |= 0x2;
	}
	execve(cmd->path, cmd->cmd, envp);
	stat = perror_minishell(NCMD, cmd->cmd[0]);
	if (cmd->malloced & 0x1)
		ft_free_pp((void **)cmd->cmd);
	else
		free(cmd->cmd);
	if (cmd->malloced & 0x2)
		free ( cmd->path);
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
			switch_streams(cmd->fd[0], cmd->fd[1], STDOUT_FILENO);
		dup_file(cmd);
		child_process(cmd, envp);
	}
	if (cmd->infile != STDIN_FILENO)
		close(cmd->infile);
	if (cmd->outfile != STDOUT_FILENO)
		close(cmd->outfile);
	// free(cmd->cmd);
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
		switch_streams((*cmd)->fd[1], (*cmd)->fd[0], STDIN_FILENO);
		(*cmd) = (*cmd)->next;
	}
}

int	exec_pipe(t_cmd *cmd, char **envp)
{
	t_cmd	*t_cmd;
	pid_t	pid;

	if (cmd->ctrl_op != PIPE)
		return (0);
	pid = fork();
	if (pid == -1)
		exit(perror_minishell(errno, "Fork child_process"));
	t_cmd = cmd;
	if (!pid)
	{
		pipe_loop(&cmd, &envp);
		if (!exec_builtins(cmd, &envp, CHILD))
			exec_cmd(cmd, envp, 0);
		wait_cmd(t_cmd, PIPE);
		exit(*get_status());
	}
	while(t_cmd->ctrl_op == PIPE)
	{
		if (t_cmd->infile != STDIN_FILENO)
			close(t_cmd->infile);
		if (t_cmd->outfile != STDOUT_FILENO)
			close(t_cmd->outfile);	
		free(t_cmd->cmd);
		t_cmd = t_cmd->next;
	}
	if (t_cmd->infile != STDIN_FILENO)
		close(t_cmd->infile);
	if (t_cmd->outfile != STDOUT_FILENO)
		close(t_cmd->outfile);
	free(t_cmd->cmd);
	waitpid(pid, get_status(), 0);
	return (1);
}
