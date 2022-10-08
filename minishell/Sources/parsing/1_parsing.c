/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_parsing.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/10/08 16:58:28 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	find_next_word(char **command, int *status, int *nb_word, char **cmd)
{
	char	*str;

	while (check_metacharacter(command, R_INVISIBLE))
		;
	str = *command;
	while (**command != '\0' && !pass_quote(command, status)
		&& !check_metacharacter(command, METACHARACTER))
		;
	if (ft_str_len(str))
	{
		*cmd = str;
		(*nb_word)++;
	}
}

/*
	// else if (command[0][0] == '(')
	//  	return (parsing_brace(command, cmd, nb_word));
*/
int	parsing_ctrl_op(char **command, t_cmd **cmd, int *nb_word, char **envp)
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
	return (perror_minishell(TOKENERR, *command));
}

// TODO Que veux dire msltadd?
// TODO Pourquoi une Calloc avec caractere 20(int)?
t_cmd	*ft_mlstadd(t_cmd *cmd, int *status)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (new)
	{
		new->cmd = (char **)ft_calloc(20, sizeof(char *));
		if (new->cmd)
		{
			new->next = NULL;
			new->status = 0;
			new->ctrl_op = END;
			new->infile = STDIN_FILENO;
			new->outfile = STDOUT_FILENO;
			if (cmd)
				cmd->next = new;
			return (new);
		}
		free(new);
	}
	*status = errno;
	perror("minishell:");
	return (NULL);
}
