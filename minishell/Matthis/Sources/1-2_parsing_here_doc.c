/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-2_parsing_here_doc.c                             :+:      :+:    :+:   */
/*   By: sbouras <sbouras@student.42quebec.com>       +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/06/13 15:10:10 by jrossign         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_limiter(int fd, char *limiter)
{
	char	*line;

	line = readline(">");
	while (line)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			close(fd);
			free(line);
			return (1);
		}
		ft_putstr_fd(line, fd);
		free(line);
		line = readline(">");
	}
	close(fd);
	free(line);
	return (0);
}

int	parsing_here_doc(char **command, t_cmd *cmd, int *trig)
{
	int		status;
	char	*file;
	char	c;
	pid_t	pid;
	int		fd[2];

	status = parsing_invisible_characters(command, trig);
	status = parsing_invisible_characters(command, trig);
	c = find_next_word(command, &file);
	printf("caractre->%s\ncommand -> %s\n", file, *command);
	if (file && *file)
	{
		if (pipe(fd) != -1)
		{
			cmd->infile = fd[READ_END];
			pid = fork();
			if (pid != -1)
			{
				if (pid == 0)
				{
					close(fd[READ_END]);
					if (check_limiter(fd[WRITE_END], file))
						exit(EXIT_SUCCESS);
					exit(EXIT_FAILURE);
				}
				else
				{
					close(fd[WRITE_END]);
					cmd->infile = fd[READ_END];
					wait(&status);
					return (status);
				}
			}
			close(fd[0]);
			close(fd[1]);
		}
		perror("minishell:");
		**command = c;
		return (1);
	}
	**command = c;
	command[0][1] = '\0';
	return (130);
}
