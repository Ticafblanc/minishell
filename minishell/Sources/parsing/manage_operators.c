/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_operators.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/10/16 21:47:13 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	parsing_and_or(char **command, t_cmd **cmd, int *nb_word)
{
	if (**(*cmd)->cmd != **command)
	{
		(*cmd)->cmd[(*nb_word)] = NULL;
		if (command[0][0] == '&')
			(*cmd)->ctrl_op = AND;
		else
			(*cmd)->ctrl_op = OR;
		check_metacharacter(command, R_METACHARACTER);
		check_metacharacter(command, R_METACHARACTER);
		if (!ft_str_len((*cmd)->cmd[--(*nb_word)]))
			(*cmd)->cmd[(*nb_word)] = NULL;
		(*cmd) = ft_mlstadd(*cmd);
		(*nb_word) = 0;
		return (0);
	}
	command[0][2] = '\0';
	return (perror_minishell(TOKENERR, *command));
}

int	parsing_pipe(char **command, t_cmd **cmd, int *nb_word)
{
	if (**(*cmd)->cmd != **command && **command)
	{
		(*cmd)->ctrl_op = PIPE;
		check_metacharacter(command, R_METACHARACTER);
		(*cmd)->cmd[0] = ft_strdup("minishell");
		(*cmd)->cmd[1] = ft_strdup("-c");
		(*cmd)->cmd[2] = ft_rev_split((const char **)(*cmd)->cmd, 32);
		(*cmd)->cmd[3] = NULL;
		(*cmd) = ft_mlstadd(*cmd);
		(*nb_word) = 0;
		return (0);
	}
	command[0][1] = '\0';
	return (perror_minishell(TOKENERR, *command));
}

int	manage_operators(char **command, t_cmd **cmd, int *nb_word, char **envp)
{
	(void) envp;
	if (**command == '\0')
		return (0);
	if (check_metacharacter(command, R_INVISIBLE))
		return (0);
	if ((command[0][0] == '|' && command[0][1] == '|')
		|| (command[0][0] == '&' && command[0][1] == '&'))
		return (parsing_and_or(command, cmd, nb_word));
	else if (**command == '|')
		return (parsing_pipe(command, cmd, nb_word));
	else
		command[0][1] = '\0';
	set_status(perror_minishell(TOKENERR, *command));
	return (get_value_status());
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
			*(new->cmd) = NULL;
			new->ctrl_op = END;
			new->path = NULL;
			new->infile = STDIN_FILENO;
			new->outfile = STDOUT_FILENO;
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
