/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 21:37:46 by tonted            #+#    #+#             */
/*   Updated: 2022/11/05 19:50:12 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO Change name function
// static int	_child_process(int fd[2])
// {
// 	char	*str;

// 	signal(SIGINT, handle_exec);
// 	close(fd[STDIN_FILENO]);
// 	str = readline("> ");
// 	while (!str || !*str)
// 	{
// 		if (!str)
// 			exit(perror_minishell(TOKENERR, "end of file"));
// 		str = readline("> ");
// 	}
// 	ft_putstr_fd(str, fd[STDOUT_FILENO]);
// 	free(str);
// 	close(fd[STDOUT_FILENO]);
// 	exit(EXIT_SUCCESS);
// }

// static int	check_command(char **command, int *status)
// {
// 	char	*str;
// 	pid_t	pid;
// 	int		fd[2];

// 	if (pipe(fd) == -1)
// 		return (perror_minishell(errno, "Fork child_process"));
// 	pid = fork();
// 	if (pid == -1)
// 		return (perror_minishell(errno, "Fork child_process"));
// 	if (!pid)
// 		_child_process(fd);
// 	close(fd[STDOUT_FILENO]);
// 	waitpid(pid, status, 0);
// 	if (!*status)
// 	{
// 		str = get_next_line(fd[STDIN_FILENO]);
// 		*command = str;
// 	}
// 	close(fd[STDIN_FILENO]);
// 	return (*status);
// }

t_cmd	*ft_mlstadd(t_cmd *cmd)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (new)
	{
		new->cmd = (char **)ft_calloc(20, sizeof(char *));
		if (new->cmd)
		{
			*(new->cmd) = NULL;
			new->ctrl_op = END;
			new->path = NULL;
			new->infile = STDIN_FILENO;
			new->outfile = STDOUT_FILENO;
			new->fd[STDIN_FILENO] = STDIN_FILENO;
			new->fd[STDOUT_FILENO] = STDOUT_FILENO;
			new->next = NULL;
			if (cmd)
				cmd->next = new;
			return (new);
		}
		free(new);
	}
	set_status(errno);
	perror("minishell:");
	return (NULL);
}

static void	parsing_loop(char **command, t_cmd *t_cmd, char **envp, char **save);

//TODO Manage signals
static void	get_sequel(char **save, t_cmd *cmd, char **envp)
{
	char	*sequel;
	char	*tmp;

	signal(SIGINT, handle_prompt);
	signal(SIGQUIT, SIG_IGN);
	tmp = *save;
	sequel = readline("> ");
	//manage if EOF
	*save = ft_strjoin(*save, sequel);
	free(tmp);
	parsing_loop(&sequel, cmd, envp, save);
}

/*
	// char	*temp;
	// TODO necessaire?
	// if (**command == '\0' && !t_cmd->cmd[nb_word - 1])
	// {
	// 	// *status = check_command(command, status);
	// 	printf("HERE\n");
	// 	temp = ft_strjoin(save, *command);
	// 	free(save);
	// 	save = temp;
	// }
*/
static void	parsing_loop(char **command, t_cmd *t_cmd, char **envp, char **save)
{
	int		nb_word;

	nb_word = 0;
	while (!(get_value_status()) && **command != '\0')
	{
		find_next_word(command, &nb_word, &t_cmd->cmd[nb_word]);
		if (**command && ft_strchr(REDIR, **command))
			manage_redir(command, t_cmd, &nb_word);
		if (**command && ft_strchr(OPERATOR, **command))
			manage_ope(command, &t_cmd, &nb_word, envp);
		if (**command && ft_strchr(BRACES, **command))
			manage_braces(command, &t_cmd, &nb_word, envp);
		if (**command == '\0' && !t_cmd->cmd[0])
			get_sequel(save, t_cmd, envp);
	}
}

t_cmd	*parsing(char *command, t_cmd **cmd, char **envp)
{
	char	*save;

	*cmd = ft_mlstadd((*cmd));
	save = ft_strdup(command);
	parsing_loop(&command, *cmd, envp, &save);
	wait_cmd(*cmd, HERE_DOC);
	add_history(save);
	free(save);
	if (get_value_status())
		return (NULL);
	return (*cmd);
}
