/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/10/26 11:56:52 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	child_process(t_cmd *cmd, char **envp)
{
	int	stat;

	if (cmd->ctrl_op == PIPE)
		switch_streams(cmd->fd[0], cmd->fd[1], 1);
	dup_file(cmd);
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
		child_process(cmd, envp);
	}
	waitpid(cmd->pid, get_status(), options);
}

static void	pipe_loop(t_cmd **cmd, char ***envp)
{
	while ((*cmd)->ctrl_op == PIPE)
	{
		if (pipe((*cmd)->fd) == -1)
			exit(perror_minishell(errno, "Fork child_process"));
		if ((*cmd)->next->infile == STDIN_FILENO)
			(*cmd)->next->infile = (*cmd)->fd[STDIN_FILENO];
		if (!exec_builtins(*cmd, envp, CHILD))
			exec_cmd(*cmd, *envp, WNOHANG);
		*cmd = (*cmd)->next;
	}
}

int	exec_pipe(t_cmd *cmd, char **envp)
{
	t_cmd	*t_cmd;

	if (cmd->ctrl_op != PIPE)
		return (0);
	t_cmd = cmd;
	pipe_loop(&cmd, &envp);
	if (!exec_builtins(cmd, &envp, CHILD))
		exec_cmd(cmd, envp, WNOHANG);
	wait_cmd(t_cmd, PIPE);
	return (1);
}
