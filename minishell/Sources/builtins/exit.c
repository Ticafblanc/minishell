/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblanco <tblanco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 09:11:19 by tonted            #+#    #+#             */
/*   Updated: 2022/11/23 21:13:46 by tblanco          ###   ########.fr       */
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

int	exec_exit(int process, char ***envp, t_cmd *cmd)
{
	int	status;

	if (process == MAIN)
		printf("exit\n");
	if (cmd->cmd[1] && !is_number(cmd->cmd[1]))
	{
		dprintf (2, "minishell: exit: %s: numeric argument required\n",
			cmd->cmd[1]);
		ft_free_pp((void **)*envp);
		free_next_cmds(cmd->begin);
		exit(EXIT_FAILURE);
	}
	if (cmd->cmd[1] && cmd->cmd[2])
	{
		dprintf (2, "minishell: exit: too many arguments\n");
		set_status(1);
		return (EXIT_FAILURE);
	}
	if (cmd->cmd[1])
	{
		status = ft_atoi(cmd->cmd[1]);
		ft_free_pp((void **)*envp);
		free_next_cmds(cmd->begin);
		exit(status);
	}
	ft_free_pp((void **)*envp);
	free_next_cmds(cmd->begin);
	exit(EXIT_SUCCESS);
	return (EXIT_FAILURE);
}
