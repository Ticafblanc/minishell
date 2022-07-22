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

int	perror_minishell(int *status, char *command)
{
	if (*status)
	{
		if (*status == NCMD)
		{
			dprintf(2,"minishell: %s: command not found: ", command);
			*status += 128;
		}
		else if (*status == 34 || *status == 39)
		{
			dprintf(2,"minishell: syntax error `%c' not close\n", (char)(*status));
			*status = 126;
		}

		else 
		{
			dprintf(2,"minishell: syntax error near unexpected token `%c'\n", (char)(*status));
			*status += 128;
		}
	}
	return (status);
}