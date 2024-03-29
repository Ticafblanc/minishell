/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblanco <tblanco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/11/23 22:11:43 by tblanco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	check_limiter(int fd[2], char *limiter)
{
	char	*line;

	line = readline("> ");
	while (line)
	{
		if (ft_strncmp(line, limiter, ft_strlen(line) + 1) == 0)
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

static int	here_doc(t_cmd *cmd, char *limiter)
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
				exit(EXIT_SUCCESS);
			}
		}
		close(fd[STDOUT_FILENO]);
		waitpid(cmd->pid, get_status(), 0);
		return (fd[STDIN_FILENO]);
	}
	return (-1);
}

static int	get_redir(char **command)
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

static void	set_redir(int king, char *file, t_cmd *cmd, char **command)
{
	char	c;

	c = **command;
	**command = '\0';
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
	**command = c;
}

int	manage_redir(char **command, t_cmd *cmd, int *nb_word)
{
	int		king;
	char	*file;

	king = get_redir(command);
	file = find_next_word_redir(command);
	if (!file)
	{
		if (king == HERE_DOC || ft_strchr(REDIR, **command))
			set_status(perror_minishell(TOKENERR, *command));
		return (get_value_status());
	}
	if (*file != **command)
	{
		set_redir(king, file, cmd, command);
		if (*nb_word > 0)
			(*nb_word)--;
		cmd->flag |= F_HD | NOT_EMPTY;
		return (0);
	}
	command[0][1] = '\0';
	set_status(perror_minishell(TOKENERR, *command));
	return (get_value_status());
}
