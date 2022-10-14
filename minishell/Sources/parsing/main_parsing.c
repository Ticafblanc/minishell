/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 21:37:46 by tonted            #+#    #+#             */
/*   Updated: 2022/10/14 02:33:31 by tonted           ###   ########.fr       */
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

char	*parsing_loop(char **command, t_cmd *t_cmd, char **envp)
{
	int		nb_word;
	// char	*temp;
	char	*save;

	nb_word = 0;
	save = ft_strdup(*command);
	while (!(get_status()) && **command != '\0')
	{
		find_next_word(command, &nb_word, &t_cmd->cmd[nb_word]);
		if (**command && ft_strchr(REDIR, **command))
			manage_redir(command, t_cmd, &nb_word);
		if (**command && ft_strchr(OPERATOR, **command))
			manage_operators(command, &t_cmd, &nb_word, envp);
		// TODO necessaire?
		// if (**command == '\0' && !t_cmd->cmd[nb_word - 1])
		// {
		// 	// *status = check_command(command, status);
		// 	printf("HERE\n");
		// 	temp = ft_strjoin(save, *command);
		// 	free(save);
		// 	save = temp;
		// }

	}
	return (save);
}

t_cmd	*parsing(char *command, t_cmd **cmd, char **envp)
{
	char	*save;

	*cmd = ft_mlstadd((*cmd));
	save = parsing_loop(&command, *cmd, envp);
	wait_cmd(*cmd, HERE_DOC);
	if (get_status())
		return (NULL);
	add_history(save);
	free(save);
	return (*cmd);
}
