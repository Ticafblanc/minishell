/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 02:32:28 by tonted            #+#    #+#             */
/*   Updated: 2022/11/02 09:18:01 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ERRNO_PRINT "minishell: %s: %s \n"
#define NCMD_PRINT "minishell: %s: command not found\n"
#define QNC_PRINT "minishell: syntax error `%c' not close\n"
#define TOKERR_PRINT "minishell: syntax error near unexpected token `%s'\n"

int	perror_minishell(int status, char *command)
{
	set_status(status);
	if (status == errno)
	{
		dprintf (2, ERRNO_PRINT, command, strerror(errno));
		set_status(1);
		status = 1;
	}
	else if (status == NCMD)
		dprintf (2, NCMD_PRINT, command);
	else if (status == QNC)
		dprintf (2, QNC_PRINT, *command);
	else if (status == TOKENERR)
		dprintf (2, TOKERR_PRINT, command);
	return (status);
}
