/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/10/21 23:07:19 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int static	check_limiter(int fd[2], char *limiter)
{
	char	*line;

	line = readline("> ");
	while (line)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			close(fd[STDOUT_FILENO]);
			free(line);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(line, fd[STDOUT_FILENO]);
		ft_putchar_fd('\n', fd[STDOUT_FILENO]);
		free(line);
		line = readline("> ");
	}
	close(fd[STDOUT_FILENO]);
	free(line);
	exit(EXIT_SUCCESS);
}

int	static	here_doc(t_cmd *cmd, char *limiter)
{
	int		fd[2];

	if (pipe(fd) != -1)
	{
		cmd->pid = fork();
		if (cmd->pid != -1)
		{
			if (!cmd->pid)
			{
				signal(SIGINT, handle_exec);
				close(fd[STDIN_FILENO]);
				check_limiter(fd, limiter);
			}
		}
		close(fd[STDOUT_FILENO]);
		return (fd[STDIN_FILENO]);
	}
	return (-1);
}

int static	get_redir(char **command)
{
	if (**command == '<')
	{
		*(*command)++ = '\0';
		if (**command == '<')
		{
			*(*command)++ = '\0';
			return (HERE_DOC);
		}
		else
			return (INFILE);
	}	
	else
	{
		*(*command)++ = '\0';
		if (**command == '>')
		{
			*(*command)++ = '\0';
			return (APPEND);
		}
		else
			return (OUTFILE);
	}
	return (-1);
}

void static	set_redir(int king, char *file, t_cmd *cmd)
{
	if (king == INFILE)
		cmd->infile = open(remove_quote(file), O_RDONLY, 0777);
	else if (king == OUTFILE)
		cmd->outfile = open(remove_quote(file), O_WRONLY | O_CREAT
				| O_TRUNC, 0777);
	else if (king == APPEND)
		cmd->outfile = open(remove_quote(file), O_WRONLY | O_CREAT
				| O_APPEND, 0777);
	else if (king == HERE_DOC)
		cmd->infile = here_doc(cmd, remove_quote(file));
	if (cmd->infile == -1 || cmd->outfile == -1)
		set_status(perror_minishell(errno, file));
}

int	manage_redir(char **command, t_cmd *cmd, int *nb_word)
{
	int		king;
	char	*file;
	char	c;

	king = get_redir(command);
	file = find_next_word_redir(command);
	if (!file)
		return (0);
	if (*file != **command)
	{
		c = **command;
		**command = '\0';
		set_redir(king, file, cmd);
		**command = c;
		(*nb_word)--;
		return (get_value_status());
	}
	command[0][1] = '\0';
	set_status(perror_minishell(TOKENERR, *command));
	return (get_value_status());
}
