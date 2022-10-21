/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_braces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:25:28 by tonted            #+#    #+#             */
/*   Updated: 2022/10/21 23:06:57 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool static	is_next_operator(char **command)
{
	int	i;

	i = 0;
	while (**command)
	{
		if (ft_strchr("|&", **command))
			return (true);
		if (!ft_strchr(WHITESPACES, **command))
			return (false);
	}
	return (true);
}

int	static	find_next_brace(char **command, t_cmd **cmd)
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
	(void) envp;
	if (**command == '(' && !*(*cmd)->cmd)
	{
		(*cmd)->ctrl_op = BRACE;
		if (!find_next_brace(command, cmd) && is_next_operator(command))
			return (get_value_status());
	}
	set_status(perror_minishell(TOKENERR, *command));
	return (get_value_status());
}
