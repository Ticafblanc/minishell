/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-1_parsing_file.c                                 :+:      :+:    :+:   */
/*   By: sbouras <sbouras@student.42quebec.com>       +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/06/13 15:10:10 by jrossign         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
if ((*command == '<' && *command == *command + 1))
		// 	*status = parsing_redir(&command, *cmd, HERE_DOC);
		// else if ((*command == '>' && *command == *command + 1))
		// 	*status = parsing_redir(&command, *cmd, APPEND);
		// else if (*command == '<')
		// 	*status = parsing_redir(&command, *cmd, INFILE);
		// else if (*command == '>')
		// 	*status = parsing_redir(&command, *cmd, OUTFILE);
// int	check_limiter(int fd[2], char *limiter)
// {
// 	char	*line;

// 	close(fd[READ_END]);
// 	line = readline(">");
// 	while (line)
// 	{
// 		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
// 		{
// 			close(fd);
// 			free(line);
// 			exit(EXIT_SUCCESS);
// 		}
// 		ft_putstr_fd(line, fd);
// 		free(line);
// 		line = readline(">");
// 	}
// 	close(fd);
// 	free(line);
// 	exit(EXIT_SUCCESS);
// }

// int	parsing_here_doc(char *limiter)
// {
// 	pid_t	pid;
// 	int		fd[2];

// 	if (pipe(fd) != -1)
// 	{
// 		pid = fork();
// 		if (pid != -1)
// 		{
// 			if (pid == 0)
// 				check_limiter(fd, limiter);
// 			close(fd[WRITE_END]);
// 			wait(NULL);
// 			return (fd[READ_END]);
// 		}
// 		close(fd[0]);
// 		close(fd[1]);
// 	}
// 	return (-1);
// }

int	parsing_redir(char **command, t_cmd *cmd, int *status)
{
    int     king;
	char	*file;
	char	c;
	char	m;
	int		r;

    file = find_arg(command, &king)
	c = **command;
	r = 1;
	parsing_invisible_characters(command);
	if (**command == c && (**command == '<' || **command == '>'))
		r = parsing_invisible_characters(command);
	m = find_next_word(command, &file);
	printf("infile->%s\ncommand -> %s\n", file, *command);
	if (c > 0)
	{
		if (c == '<' && r == 1)
			cmd->infile = open(remove_quote(file), O_RDONLY, 0777);
		else if (c == '>' && r == 1)
			cmd->outfile = open(remove_quote(file), O_WRONLY | O_CREAT | O_TRUNC, 0777);
		else if (c == '>' && r == 0)
			cmd->outfile = open(remove_quote(file), O_WRONLY | O_CREAT | O_APPEND, 0777);
		else
			cmd->infile = parsing_here_doc(remove_quote(file));
		if (cmd->infile == -1 || cmd->outfile == -1)
			return (perror_minishell(errno, file));
		**command = m;
		return (0);
	}
	return (130);
}






// // int	parsing_app_redir_out(char **command, t_cmd *cmd, int *trig)
// // {
// // 	char	*file;
// // 	char	c;

// // 	parsing_invisible_characters(command, trig);
// // 	parsing_invisible_characters(command, trig);
// // 	c = find_next_word(command, &file);
// // 	printf("app_file->%s\n", file);
// // 	if (file && *file)
// // 	{
// // 		cmd->outfile = open(remove_quote(file), O_WRONLY | O_CREAT | O_APPEND, 0777);
// // 		if (cmd->outfile == -1)
// // 		{
// // 			dprintf(2,"minishell: %s: %s \n", file, strerror(errno));
// // 			return (1);
// // 		}
// // 		**command = c;
// // 		return (0);
// // 	}
// // 	**command = c;
// // 	command[0][1] = '\0';
// // 	return(130);
// // }

// // int	parsing_redir_out(char **command, t_cmd *cmd, int *trig)
// // {
// // 	char	*file;
// // 	char	c;

// // 	parsing_invisible_characters(command, trig);
// // 	c = find_next_word(command, &file);
// // 	printf("outfile->%s\n", file);
// // 	if (file && *file)
// // 	{
// // 		cmd->outfile = open(remove_quote(file), O_WRONLY | O_CREAT | O_TRUNC, 0777);
// // 		if (cmd->outfile == -1)
// // 		{
// // 			dprintf(2,"minishell: %s: %s \n", file, strerror(errno));
// // 			return (1);
// // 		}
// // 		**command = c;
// // 		return (0);
// // 	}
// // 	**command = c;
// // 	command[0][1] = '\0';
// // 	return(130);
// // }
