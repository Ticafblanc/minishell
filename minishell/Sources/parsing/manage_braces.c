/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_braces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 14:25:28 by tonted            #+#    #+#             */
/*   Updated: 2022/10/18 19:28:49 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_next_brace(char **command, t_cmd **cmd)
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
	(*cmd)->cmd[(*nb_word)] = NULL;
	if (*(*cmd)->cmd)
		(*cmd) = ft_mlstadd(*cmd);
	(*cmd)->ctrl_op = BRACE;
	if (**command == '(')
		if (!find_next_brace(command, cmd))
			return (get_value_status());
	set_status(perror_minishell(TOKENERR, *command));
	return (get_value_status());
}
