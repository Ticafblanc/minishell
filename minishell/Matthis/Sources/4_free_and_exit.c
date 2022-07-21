/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_free_and_exit.c                                  :+:      :+:    :+:   */
/*   By: sbouras <sbouras@student.42quebec.com>       +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/06/11 18:30:06 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	perror_minishell(int *status, char *command)
{
	if (*status)
	{
		if (*status == NCMD)
		{
			dprintf(2,"minishell: %s: command not found: ", command);
			*status = 127;
		}
		else 
		{
			dprintf(2,"minishell: syntax error near unexpected token `%c'", status);
			*status = 258;
		}
	}
	return ;
}