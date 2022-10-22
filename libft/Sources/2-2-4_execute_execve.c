/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-2-4_execute_execve.c                             :+:      :+:    :+:   */
/*   By: sbouras <sbouras@student.42quebec.com>       +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/06/13 15:10:10 by jrossign         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// void	ft_execve(char *argv)
// {
// 	char	**cmd;
// 	char	*path;

// 	cmd = ft_split(argv, ' ');
// 	if (*cmd[0] == '/' || *cmd[0] == '.' || *cmd[0] == '~')
// 		path = cmd[0];
// 	else
// 		path = find_path(cmd[0], envp);
// 	execve(path, cmd, envp);
// 	ft_free_pp(cmd);
// 	free(path);
// 	ft_exit_perror("command not found", 127);
// }

// void	child_process(char *argv, char **envp)
// {
// 	pid_t	pid;
// 	int		fd[2];
// 	int		status;

// 	if (pipe(fd) == -1)
// 		ft_exit_perror("Pipe child_process", EXIT_FAILURE);
// 	pid = fork();
// 	if (pid == -1)
// 		ft_exit_perror("Fork child_process", EXIT_FAILURE);
// 	if (pid > 0)
// 	{
// 		close(fd[FD_WRITE]);
// 		dup2(fd[FD_READ], STDIN_FILENO);
// 		close(fd[FD_READ]);
// 		waitpid(pid, &status, WNOHANG);
// 	}
// 	else
// 	{
// 		close(fd[FD_READ]);
// 		dup2(fd[FD_WRITE], STDOUT_FILENO);
// 		close(fd[FD_WRITE]);
// 		ft_execve(argv, envp);
// 	}
// }
