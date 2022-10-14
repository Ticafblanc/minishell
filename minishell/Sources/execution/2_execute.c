/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_execute.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/10/14 21:16:50 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	child_process(t_cmd *cmd, char **envp, int fd[2])
{
	if (cmd->ctrl_op == PIPE)
		switch_streams(fd[STDIN_FILENO], fd[STDOUT_FILENO], STDOUT_FILENO);
	dup_file(cmd);
	if (*cmd->cmd[0] == '/' || *cmd->cmd[0] == '.' || *cmd->cmd[0] == '~')
		cmd->path = cmd->cmd[0];
	else
		cmd->path = find_path(cmd->cmd[0], envp);
	execve(cmd->path, cmd->cmd, envp);
	exit(perror_minishell(NCMD, cmd->cmd[0]));
}

void	exec_cmd(t_cmd *cmd, char **envp, int options)
{
	int		fd[2];

	if (cmd->ctrl_op == PIPE)
		if (pipe(fd) == -1)
			exit(perror_minishell(errno, "Fork child_process"));
	cmd->pid = fork();
	if (cmd->pid == -1)
		exit(perror_minishell(errno, "Fork child_process"));
	if (!cmd->pid)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		child_process(cmd, envp, fd);
	}
	if (cmd->ctrl_op == PIPE)
		switch_streams(fd[STDOUT_FILENO], fd[STDIN_FILENO], STDIN_FILENO);
	waitpid(cmd->pid, get_status(), options);
}

static void	pipe_loop(t_cmd **cmd, char ***envp)
{
	while ((*cmd)->ctrl_op == PIPE)
	{
		if (!exec_builtins(*cmd, envp, CHILD))
			exec_cmd(*cmd, *envp, WNOHANG);
		*cmd = (*cmd)->next;
	}
}

int	exec_pipe(t_cmd *cmd, char **envp)
{
	pid_t	pid;
	t_cmd	*t_cmd;

	if (cmd->ctrl_op != PIPE)
		return (0);
	pid = fork();
	if (pid == -1)
		exit(perror_minishell(errno, "Fork child_process"));
	if (!pid)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		t_cmd = cmd;
		pipe_loop(&cmd, &envp);
		if (!exec_builtins(cmd, &envp, CHILD))
			exec_cmd(cmd, envp, WNOHANG);
		wait_cmd(t_cmd, PIPE);
		close(STDIN_FILENO);
		exit(get_value_status());
	}
	waitpid(pid, get_status(), 0);
	return (1);
}
