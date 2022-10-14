/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 02:32:28 by tonted            #+#    #+#             */
/*   Updated: 2022/10/14 03:10:00 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	perror_minishell(int status, char *command)
{
	set_status(status);
	printf("<<<<< ERROR %d : %s >>>>>\n", status, command);
	if (status == errno)
	{
		dprintf (2, "minishell: %s: %s \n", command, strerror(errno));
		set_status(1);
		status = 1;
	}
	else if (status == NCMD)
		dprintf (2, "minishell: %s: command not found\n", command);
	else if (status == QNC)
		dprintf (2, "minishell: syntax error `%c' not close\n", *command);
	else if (status == TOKENERR)
	{
		dprintf (2, "minishell: syntax error near unexpected token `%s'\n",
			command);
	}
	return (status);
}
