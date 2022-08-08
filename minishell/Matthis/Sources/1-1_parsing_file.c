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

static char	*find_redir(char **command, int *status, int *king)
{
	if (**command == '<')
	{
		check_metacharacter(command, R_METACHARACTER);
		*king = INFILE;
		if (**command == '<')
		{
			check_metacharacter(command, R_METACHARACTER);
			*king = HERE_DOC;
		}
	}	
	else if (**command == '>')
	{
		check_metacharacter(command, R_METACHARACTER);
		*king = OUTFILE;
		if (**command == '>')
		{
			check_metacharacter(command, R_METACHARACTER);
			*king = APPEND;
		}
	}
	else
		return (NULL);
	return(find_next_word(command, status));
}

static int	check_limiter(int fd[2], char *limiter)
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

int	parsing_here_doc(t_cmd *cmd, char *limiter)
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

int	parsing_redir(char **command, t_cmd *cmd, int *status, int *nb_word)
{
    int     king;
	char	*file;
	char	c;

    file = find_redir(command, status, &king);
	if (!file)
		return (0);
	if (*file != **command)
	{
		c = **command;
		**command = '\0';
		if (king == INFILE)
			cmd->infile = open(remove_quote(file), O_RDONLY, 0777);
		else if (king == OUTFILE)
			cmd->outfile = open(remove_quote(file), O_WRONLY | O_CREAT | O_TRUNC, 0777);
		else if (king == APPEND)
			cmd->outfile = open(remove_quote(file), O_WRONLY | O_CREAT | O_APPEND, 0777);
		else if (king == HERE_DOC)
			cmd->infile = parsing_here_doc(cmd, remove_quote(file));
		if (cmd->infile == -1 || cmd->outfile == -1)
			*status = perror_minishell(errno, file);
		**command = c;
		(*nb_word)--;
		return (*status);
	}
	command[0][1] = '\0';
	*status = perror_minishell(TOKENERR, *command);
	return (*status);
}

char *remove_quote(char *command)
{
    int     i;
    char    c;
    int     trig;
    char    *new_command;

    i =  0;
    trig = 0;
    new_command = command;
    while (*command != '\0')
    {
        if (!trig && (*command == 34 || *command == 39))
        {
            c = *command;
            i++;
            trig = 1;
        }
        else if (trig && c == *command)
        {
            i++;
            trig = 0;
        }
        *command = command[i];
        command++;
    }
	command -= i;
	*command = '\0';
    return (new_command);
}
