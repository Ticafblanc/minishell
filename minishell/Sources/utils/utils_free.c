/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblanco <tblanco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 21:21:15 by tonted            #+#    #+#             */
/*   Updated: 2022/11/23 17:15:03 by tblanco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_freetabstr(char **tab)
{
	int	i;

	if (*tab)
	{
		i = 0;
		while ((tab)[i])
			free((tab)[i++]);
		free(tab);
		tab = NULL;
	}
}

void	free_null(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

int	exit_free_envp(char ***envp)
{
	ft_free_pp((void **)*envp);
	printf("exit\n");
	return (EXIT_SUCCESS);
}

void	free_next_cmds(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		if (cmd->cmd)
			ft_free_pp((void **)cmd->cmd);
		tmp = cmd;
		cmd = cmd->next;
		free_null(tmp);
	}
}

void	wait_next_cmds(t_cmd *cmd)
{
	t_cmd	*tmp;

	while (cmd)
	{
		if (cmd->ctrl_op == PIPE)
			waitpid(cmd->pid, get_status(), 0);
		if (cmd->cmd)
			ft_free_pp((void **)cmd->cmd);
		tmp = cmd;
		cmd = cmd->next;
		free_null(tmp);
	}
}
