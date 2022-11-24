/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblanco <tblanco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 21:37:46 by tonted            #+#    #+#             */
/*   Updated: 2022/11/23 22:12:58 by tblanco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_command_child(int fd[2])
{
	char	*str;

	signal(SIGINT, handle_exec);
	close(fd[STDIN_FILENO]);
	str = readline("> ");
	while (!str || !*str)
	{
		if (!str)
			exit(perror_minishell(TOKENERR, "end of file"));
		free_null(str);
		str = readline("> ");
	}
	ft_putstr_fd(str, fd[STDOUT_FILENO]);
	free(str);
	close(fd[STDOUT_FILENO]);
	exit(EXIT_SUCCESS);
}

static int	check_command(char **command, char **save, char **tmp_c)
{
	pid_t	pid;
	int		fd[2];
	char	*tmp;

	if (pipe(fd) == -1)
		return (perror_minishell(errno, "Fork child_process"));
	pid = fork();
	if (pid == -1)
		return (perror_minishell(errno, "Fork child_process"));
	if (!pid)
		check_command_child(fd);
	close(fd[STDOUT_FILENO]);
	waitpid(pid, get_status(), 0);
	*command = get_next_line(fd[STDIN_FILENO]);
	if (*command)
	{
		free(*tmp_c);
		*tmp_c = *command;
		tmp = *save;
		*save = ft_strjoin(*save, *command);
		free(tmp);
	}
	close(fd[STDIN_FILENO]);
	return (get_value_status());
}
// static void	get_sequel(char **save, t_cmd *cmd, char **envp)
// {
// 	char	*sequel;
// 	char	*tmp;
//
// 	signal(SIGINT, handle_prompt);
// 	signal(SIGQUIT, SIG_IGN);
// 	tmp = *save;
// 	sequel = readline("> ");
// 	if (!sequel)
// 	{
// 		dprintf(2, "bash: syntax error: unexpected end of file\n");
// 		set_status(TOKENERR);
// 		return ;
// 	}
// 	*save = ft_strjoin(*save, sequel);
// 	free(tmp);
// 	parsing_loop(&sequel, cmd, envp, save);
// }

static void	dup_cmds(t_cmd *t_cmd, char *tmp)
{
	int		i;

	i = 0;
	while (t_cmd->cmd[i])
	{
		t_cmd->cmd[i] = ft_strdup(t_cmd->cmd[i]);
		i++;
	}
	free_null(tmp);
}

void	parsing_loop(char *command, t_cmd *t_cmd, char **envp, char **save)
{
	int		nb_word;
	int		status;
	char	*tmp;

	tmp = command;
	nb_word = 0;
	status = 0;
	while (status <= 0)
	{
		status = find_next_word(&command, &nb_word, &t_cmd->cmd[nb_word]);
		if (nb_word > 0)
			t_cmd->flag |= NOT_EMPTY;
		if (*command && ft_strchr(REDIR, *command))
			status = manage_redir(&command, t_cmd, &nb_word);
		else if (*command && ft_strchr(OPERATOR, *command))
			status = manage_ope(&command, &t_cmd, &nb_word, envp);
		else if (*command && ft_strchr(BRACES, *command))
			manage_braces(&command, &t_cmd, &nb_word, envp);
		else if (*command == '\0' && !t_cmd->cmd[0] && !(t_cmd->flag & F_HD)
			&& !(t_cmd->flag & F_FIRST))
			status = check_command(&command, save, &tmp);
		else if (*command == '\0')
			break ;
	}
	dup_cmds(t_cmd, tmp);
}

t_cmd	*parsing(char *command, t_cmd **cmd, char **envp)
{
	char	*save;
	t_cmd	*tmp;

	*cmd = ft_mlstadd((*cmd));
	save = ft_strdup(command);
	parsing_loop(command, *cmd, envp, &save);
	tmp = *cmd;
	while (tmp)
	{
		tmp->command = command;
		tmp = tmp->next;
	}
	add_history(save);
	free(save);
	return (*cmd);
}
