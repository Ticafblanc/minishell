/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblanco <tblanco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 21:37:46 by tonted            #+#    #+#             */
/*   Updated: 2022/11/20 14:52:36 by tblanco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sequel_child(int fd[2])
{
	char	*sequel;

	signal(SIGINT, handle_exec);
	close(fd[0]);
	sequel = readline("> ");
	if (!sequel)
	{
		dprintf(2, "minishell: syntax error: unexpected end of file\n");
		exit (TOKENERR);
	}
	ft_putstr_fd(sequel, fd[1]);
	free_null(sequel);
	close (fd[1]);
	exit (EXIT_SUCCESS);
}

static void	get_sequel(char **save, t_cmd *cmd, char **envp)
{
	int		fd[2];
	char	*sequel;
	char	*tmp;
	pid_t	pid;

	tmp = *save;
	if (pipe(fd) != -1)
	{
		pid = fork();
		if (pid != -1)
		{
			if (!pid)
				sequel_child(fd);
			waitpid(pid, get_status(), 0);
		}
		close(fd[1]);
		sequel = get_next_line(fd[STDIN_FILENO]);
		close(fd[0]);
		*save = ft_strjoin(*save, sequel);
		free(tmp);
		parsing_loop(&sequel, cmd, envp, save);
	}
}

void	parsing_loop(char **command, t_cmd *t_cmd, char **envp, char **save)
{
	int		nb_word;

	nb_word = 0;
	while (!(get_value_status()))
	{
		find_next_word(command, &nb_word, &t_cmd->cmd[nb_word]);
		if (**command && ft_strchr(REDIR, **command))
			manage_redir(command, t_cmd, &nb_word);
		else if (**command && ft_strchr(OPERATOR, **command))
			manage_ope(command, &t_cmd, &nb_word, envp);
		else if (**command && ft_strchr(BRACES, **command))
			manage_braces(command, &t_cmd, &nb_word, envp);
		else if (**command == '\0' && !t_cmd->cmd[0] && !(t_cmd->flag & F_HD) && !(t_cmd->flag & F_FIRST))
			get_sequel(save, t_cmd, envp);
		else if (**command == '\0')
			break ;
	}
}

t_cmd	*parsing(char *command, t_cmd **cmd, char **envp)
{
	char	*save;

	*cmd = ft_mlstadd((*cmd));
	save = ft_strdup(command);
	parsing_loop(&command, *cmd, envp, &save);
	add_history(save);
	free(save);
	if (get_value_status())
		return (NULL);
	return (*cmd);
}
