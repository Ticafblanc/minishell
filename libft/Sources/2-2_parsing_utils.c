/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-2-1_parsing.c                                    :+:      :+:    :+:   */
/*   By: sbouras <sbouras@student.42quebec.com>       +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/06/13 15:10:10 by jrossign         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

// char	*find_path(char *cmd)
// {
// 	char	**paths;
// 	char	*path;
// 	int		i;


// 	i = 0;
// 	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == 0)
// 		i++;
// 	paths = ft_split(envp[i] + 5, ':');
// 	i = 0;
// 	cmd = ft_strjoin("/", cmd);
// 	while (paths[i])
// 	{
// 		path = ft_strjoin(paths[i], cmd);
// 		if (access(path, X_OK) == 0)
// 		{
// 			free(cmd);
// 			ft_free_pp(paths);
// 			return (path);
// 		}
// 		free(path);
// 		i++;
// 	}
// 	free(cmd);
// 	ft_free_pp(paths);
// 	return (NULL);
// }



// void	here_doc(char *limiter, int argc)
// {
// 	pid_t	pid;
// 	int		fd[2];


// 	if (pipe(fd) == -1)
// 		ft_exit_perror("Pipe here_doc", EXIT_FAILURE);
// 	pid = fork();
// 	if (pid == -1)
// 		ft_exit_perror("Fork here_doc", EXIT_FAILURE);
// 	if (pid == 0)
// 	{
// 		close(fd[FD_READ]);
// 		if (check_limiter(fd[FD_WRITE], limiter) == 1)
// 			exit(EXIT_SUCCESS);
// 	}
// 	else
// 	{
// 		close(fd[FD_WRITE]);
// 		dup2(fd[FD_READ], STDIN_FILENO);
// 		wait(NULL);
// 	}
// }
