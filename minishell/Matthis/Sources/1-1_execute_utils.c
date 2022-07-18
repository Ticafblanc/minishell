/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-2-2_dispatch_execute.c                           :+:      :+:    :+:   */
/*   By: sbouras <sbouras@student.42quebec.com>       +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/06/13 15:10:10 by jrossign         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern char **g_envp;

// //int	check_limiter(int fd, char *limiter)
// {
// 	char	*line;

// 	line = get_next_line(STDIN_FILENO);
// 	while (line)
// 	{
// 		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
// 		{
// 			close(fd);
// 			free(line);
// 			return (1);
// 		}
// 		ft_putstr_fd(line, fd);
// 		free(line);
// 		line = get_next_line(STDIN_FILENO);
// 	}
// 	close(fd);
// 	free(line);
// 	return (0);
// }

// void	here_doc(char *limiter, int argc)
// {
// 	pid_t	pid;
// 	int		fd[2];

// 	if (argc < 6)
// 		ft_exit_strerror(EINVAL, EXIT_FAILURE);
// 	if (pipe(fd) == -1)
// 		free_and_exit(PIPE_R);
// 	pid = fork();
// 	if (pid == -1)
// 		free_and_exit(FORK);
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

// int	open_outfile(t_command *cmd)
// {
// 	int		i;
// 	char	*outfile

// 	i = 0;
// 	outfile = ft_substr(cmd->to_do, 0, add_file_name(cmd->to_do));
// 	if (!outfile)
// 		free_and_exit(MEMO);
// 	if (cmd->flag_end == REPLACE_FILE)
// 	{
// 		cmd->outfile = open(argv[argc - 1],
// 				O_WRONLY | O_CREAT | O_TRUNC, 0777);
// 	}
// 	else if (cmd->flag_end == APPEND_FILE)
// 	{
// 		cmd->outfile = open(argv[argc - 1],
// 				O_WRONLY | O_CREAT | O_APPEND, 0777);
// 	}
// 	free(outfile);
// 	if (save->outfile == -1)
// 		free_and_exit(OUTFILE);
// 	dup2(save->outfile, STDOUT_FILENO);
// 	close(save->outfile);
// 	return (i);
// }

// // int	open_infile(t_command *cmd)
// // {
// // 	int		i;
// // 	char	*infile;

// // 	i = 0;
// // 	if (ft_strncmp(cmd->to_do, "<<", 2) == 0)
// // 	{
// // 		here_doc(cmd);
// // 		i += 2;
// // 		return (i);
// // 	}
// // 	else if (ft_strncmp(cmd->to_do, "<", 1) == 0)
// // 	{
// // 		cmd->to_do++;
// // 		i +=1
// // 	}
// // 	infile = ft_substr(cmd->to_do, 0, add_file_name(cmd->to_do));
// // 	if (!intfile)
// // 		free_and_exit(MEMO);
// // 	cmd->infile = open(infile, O_RDONLY, 0777);
// // 	free(infile);
// // 	if (cmd->infile == -1)
// // 		free_and_exit(INFILE);
// // 	dup2(save->infile, STDIN_FILENO);
// // 	close(save->infile);
// 	return (i);
// }

// void	dispatch_execute(t_command *cmd)
// {
// 	int	i;
	
// 	i = 0;
// 	cmd->to_do = NULL;
// 	printf("command a executer : %s\n", g_global.command);
// 	while (*cmd->to_do)
// 	{
// 		if (*cmd->to_do == '<')
// 			cmd->to_do += open_infile(cmd)
// 			child_process(argv[i++], envp);
// 		dup2(save.outfile, STDOUT_FILENO);
// 		close(save.outfile);
// 		ft_execve(argv[argc - 2], envp);
	
// }

