/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_braces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblanco <tblanco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:25:28 by tonted            #+#    #+#             */
/*   Updated: 2022/11/23 20:26:44 by tblanco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_next_operator(char **command)
{
	while (**command)
	{
		if (ft_strchr("|&", **command))
			return (true);
		if (!ft_strchr(WHITESPACES, **command))
			return (false);
		(*command)++;
	}
	return (true);
}

static int	find_next_brace(char **command, t_cmd **cmd)
{
	int	amount;

	amount = 0;
	amount++;
	*(*command)++ = '\0';
	(*cmd)->cmd[0] = *command;
	while (amount && **command)
	{
		if (**command == '(')
			amount++;
		else if (**command == ')')
			amount--;
		(*command)++;
	}
	if (!amount && *(--*command) == ')')
	{
		*(*command)++ = '\0';
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	manage_braces(char **command, t_cmd **cmd, int *nb_word, char **envp)
{
	(void)nb_word;
	(void) envp;
	if (**command == '(' && !*(*cmd)->cmd)
	{
		if (!find_next_brace(command, cmd) && is_next_operator(command)
			&& ++(*nb_word))
		{
			(*cmd)->flag |= F_BRACE;
			return (get_value_status());
		}
	}
	set_status(perror_minishell(TOKENERR, *command));
	return (get_value_status());
}
