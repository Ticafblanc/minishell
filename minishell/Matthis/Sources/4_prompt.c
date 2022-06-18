/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_prompt.c                                         :+:      :+:    :+:   */
/*   By: sbouras <sbouras@student.42quebec.com>       +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/06/13 15:10:10 by jrossign         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_global	g_global;

void	prompt_minishell(void)
{
	g_global.command = readline("Minishell % ");
	if (!g_global.command)
	{
		g_global.statut = EXIT_SUCCESS;
		return ;
	}
	if (g_global.command[0] != '\0')
		add_history(g_global.command);
}
