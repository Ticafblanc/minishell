/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0-1-1_prompt.c                                     :+:      :+:    :+:   */
/*   By: sbouras <sbouras@student.42quebec.com>       +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/06/13 15:10:10 by jrossign         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_global	g_global;

int	check_add_history(char *command)
{
	int	i;

	i = 0;
	while (command[i])
	{
		if (check_invisible_characters(command[i]) == 1)
			i++;
		else
			break;
	}
	if (command[i] == '\0')
		return (0);
	add_history(command);
	return (1);
}
		

int	prompt_minishell(void)
{
	g_global.command = readline("Minishell % ");
	if (!g_global.command)
	{
		g_global.statut = EXIT_SUCCESS;
		return (0);
	}
	else if (check_add_history(g_global.command) == 1)
		return (1);
	return (2);
}
