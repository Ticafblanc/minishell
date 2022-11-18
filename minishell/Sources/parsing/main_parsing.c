/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 21:37:46 by tonted            #+#    #+#             */
/*   Updated: 2022/11/14 22:58:02 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_link(t_cmd *new)
{
	*(new->cmd) = NULL;
	new->ctrl_op = END;
	new->path = NULL;
	new->infile = STDIN_FILENO;
	new->outfile = STDOUT_FILENO;
	new->fd[STDIN_FILENO] = STDIN_FILENO;
	new->fd[STDOUT_FILENO] = STDOUT_FILENO;
	new->flag = 0x0;
	new->next = NULL;
	new->pid = -2;
}

t_cmd	*ft_mlstadd(t_cmd *cmd)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (new)
	{
		new->cmd = (char **)ft_calloc(20, sizeof(char *));
		if (new->cmd)
		{
			init_link(new);
			set_status(0);
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

static void	get_sequel(char **save, t_cmd *cmd, char **envp)
{
	char	*sequel;
	char	*tmp;

	signal(SIGINT, handle_prompt);
	signal(SIGQUIT, SIG_IGN);
	tmp = *save;
	sequel = readline("> ");
	if (!sequel)
	{
		dprintf(2, "bash: syntax error: unexpected end of file\n");
		set_status(258);
		return ;
	}
	*save = ft_strjoin(*save, sequel);
	free(tmp);
	parsing_loop(&sequel, cmd, envp, save);
}

void	parsing_loop(char **command, t_cmd *t_cmd, char **envp, char **save)
{
	int		nb_word;

	nb_word = 0;
	while (!(get_value_status()) || t_cmd->flag & 0x2)
	{
		find_next_word(command, &nb_word, &t_cmd->cmd[nb_word]);
		if (**command && ft_strchr(REDIR, **command))
			manage_redir(command, t_cmd, &nb_word);
		else if (**command && ft_strchr(OPERATOR, **command))
			manage_ope(command, &t_cmd, &nb_word, envp);
		else if (**command && ft_strchr(BRACES, **command))
			manage_braces(command, &t_cmd, &nb_word, envp);
		else if (**command == '\0' && !t_cmd->cmd[0] && !(t_cmd->flag & FLAG_HEREDOC))
			get_sequel(save, t_cmd, envp);
		else if (**command == '\0')
			break;
	}
}

t_cmd	*parsing(char *command, t_cmd **cmd, char **envp)
{
	char	*save;

	*cmd = ft_mlstadd((*cmd));
	save = ft_strdup(command);
	parsing_loop(&command, *cmd, envp, &save);
	wait_cmd(*cmd, HERE_DOC);
	// print_cmds(*cmd);
	add_history(save);
	free(save);
	if (get_value_status())
	{
		free((*cmd)->cmd);
		(*cmd)->cmd = NULL;
		free((*cmd));
		(*cmd) = NULL;
	}	
	return (*cmd);
}
