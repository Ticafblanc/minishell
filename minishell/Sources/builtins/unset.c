/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 09:09:50 by tonted            #+#    #+#             */
/*   Updated: 2022/10/31 22:49:32 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_unset(t_cmd *cmd, char ***envp)
{
	int		com;
	int		env;
	int		n_env;

	com = 0;
	while (cmd->cmd[++com])
	{
		env = 0;
		n_env = 0;
		while (ft_len_pp((void **)envp[0] + env) > 0)
		{
			if (!strncmp(envp[0][env], cmd->cmd[com],
				ft_strlen(cmd->cmd[com])))
				env++;
			envp[0][n_env++] = envp[0][env++];
		}
		envp[0][n_env] = NULL;
	}
	return (1);
}
