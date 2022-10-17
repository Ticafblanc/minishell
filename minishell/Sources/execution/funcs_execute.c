/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funcs_execute.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/10/17 16:22:20 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	forward_to_next(char *s, int i, char c)
{
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char	**interpret_vars(t_cmd *cmd, char **envp)
{
	int		i;
	int		i_s;
	int		i_begin;
	int		i_end;
	char	*tmp;
	char	*tmp_new;
	int		i_env;

	i = 0;
	while (cmd->cmd[i])
	{
		i_s = 0;
		while (cmd->cmd[i][i_s])
		{
			if (cmd->cmd[i][i_s] == '\'')
				i_s = forward_to_next(cmd->cmd[i], i_s++, '\'');
			else if (cmd->cmd[i][i_s] == '$')
			{
				cmd->cmd[i][i_s] = '\0';
				i_end = forward_to_next(cmd->cmd[i], i_s + 1, ' ');
				cmd->cmd[i][i_end] = '\0';
				i_env = is_name_in_envp(envp, &cmd->cmd[i][i_s + 1]);
				if (i_env == -1)
					tmp = "";
				else
					tmp = get_value(envp[i_env]);
				tmp_new = ft_strjoin(cmd->cmd[i], tmp);
				// cmd->cmd[i][i_end] = ' ';
				cmd->cmd[i][i_s] = ' ';
				tmp = ft_strjoin(tmp_new, &cmd->cmd[i][i_end]);
				free_null(tmp_new);
				tmp_new = cmd->cmd[i];
				cmd->cmd[i] = remove_quote(tmp);
				char *str_tmp = ft_rev_split((const char**)cmd->cmd, ' ');
				cmd->cmd = ft_split(remove_quote(str_tmp), ' ');
			}
			i_s++;
		}
		i++;
	}
	// printf(">>>> %s\n", str_tmp);
	return (cmd->cmd);
}

static void	child_process(t_cmd *cmd, char **envp, int fd[2])
{
	if (cmd->ctrl_op == PIPE)
		switch_streams(fd[STDIN_FILENO], fd[STDOUT_FILENO], STDOUT_FILENO);
	dup_file(cmd);
	cmd->cmd = interpret_vars(cmd, envp);
	print_cmd(cmd);
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
