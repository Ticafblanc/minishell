/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 09:11:19 by tonted            #+#    #+#             */
/*   Updated: 2022/11/02 10:37:30 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_number(char *s)
{
	while (ft_isdigit(*s))
		s++;
	if (*s)
		return (false);
	return (true);
}

int	exec_exit(int process, char ***envp, char **cmd)
{
	if (ft_len_pp((void **)cmd) > 2)
	{
		dprintf (2, "minishell: exit: too many arguments\n");
		set_status(1);
		return (EXIT_FAILURE);
	}
	if (process == MAIN)
		printf("exit\n");
	if (cmd[1] && !is_number(cmd[1]))
		dprintf (2, "minishell: exit: %s: numeric argument required\n", cmd[1]);
	ft_free_pp((void **)*envp);
	exit(EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
