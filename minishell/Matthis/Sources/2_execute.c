/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_execute.c                                        :+:      :+:    :+:   */
/*   By: sbouras <sbouras@student.42quebec.com>       +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/06/13 15:10:10 by jrossign         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void dup_file(t_cmd *cmd)
{
	if (cmd->infile != STDIN_FILENO)
	{
		dup2(cmd->infile, STDIN_FILENO);
		close(cmd->infile);
	}
	if (cmd->outfile != STDOUT_FILENO)
	{
		dup2(cmd->outfile, STDOUT_FILENO);
		close(cmd->outfile);
	}
}

static char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;


	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	cmd = ft_strjoin("/", cmd);
	while (paths[i])
	{
		path = ft_strjoin(paths[i], cmd);
		if (access(path, X_OK) == 0)
		{
			free(cmd);
			ft_free_pp((void **)paths);
			return (path);
		}
		free(path);
		i++;
	}
	free(cmd);
	ft_free_pp((void **)paths);
	return (NULL);
}

static void	child_process(t_cmd *cmd, char **envp, int fd[2])
{
	if (cmd->ctrl_op == PIPE)
	{
		close(fd[STDIN_FILENO]);
		dup2(fd[STDOUT_FILENO], STDOUT_FILENO);
		close(fd[STDOUT_FILENO]);
	}
	dup_file(cmd);
	if (*cmd->cmd[0] == '/' || *cmd->cmd[0] == '.' || *cmd->cmd[0] == '~')
		cmd->path = cmd->cmd[0];
 	else
		cmd->path = find_path(cmd->cmd[0], envp);
	execve(cmd->path, cmd->cmd, envp);
	exit(perror_minishell(NCMD, cmd->cmd[0]));
}

void	exec_cmd(t_cmd *cmd, int *status, char **envp, int options)
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
	{
		close(fd[STDOUT_FILENO]);
		dup2(fd[STDIN_FILENO], STDIN_FILENO);
		close(fd[STDIN_FILENO]);
	}
	waitpid(cmd->pid, status, options);
}

int	exec_pipe(t_cmd *cmd, int *status, char **envp)
{
	pid_t	pid;
	int		i;
	t_cmd	*t_cmd;

	i = 0;
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
		while (cmd->ctrl_op == PIPE)
		{
			//print_cmd(cmd);
			if(!exec_builtins(cmd, status, &envp, CHILD))
				exec_cmd(cmd, status, envp, WNOHANG);
			cmd = cmd->next;
		}
		if(!exec_builtins(cmd, status, &envp, CHILD))
			exec_cmd(cmd, status, envp, WNOHANG);
		wait_cmd(t_cmd, status, PIPE);
		close(STDIN_FILENO);
		exit(*status);
	}
	waitpid(pid, status, 0);
	return (1);
}