/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblanco <tblanco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 09:09:50 by tonted            #+#    #+#             */
/*   Updated: 2022/11/20 11:01:11 by tblanco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	envp_remove_line(char ***envp, char *name)
{
	int		i_old;
	int		i_new;
	char	**n_envp;
	
	if (is_name_in_envp((*envp), name) >= 0)
	{
		n_envp = (char **)malloc(sizeof(char *) * (ft_len_pp((void **)(*envp))));
		if (!n_envp)
			return ;
		i_old = 0;
		i_new = 0;
		while ((*envp)[i_old])
		{
			if (!is_name_in_line((*envp)[i_old], name))
				n_envp[i_new++] = (*envp)[i_old];
			else
			{
				free((*envp)[i_old]);
				(*envp)[i_old] = NULL;
			}
			i_old++;
		}
		n_envp[i_new] = NULL;
		free((*envp));
		(*envp) = n_envp;
	}
}

int	exec_unset(t_cmd *cmd, char ***envp)
{
	int	i_arg;

	i_arg = 1;
	while (cmd->cmd[i_arg])
	{
		envp_remove_line(envp, cmd->cmd[i_arg]);
		i_arg++;
	}
	return (1);
}

// int	exec_unset(t_cmd *cmd, char ***envp)
// {
// 	int		com;
// 	int		env;
// 	int		n_env;

// 	com = 0;
// 	while (cmd->cmd[++com])
// 	{
// 		env = 0;
// 		n_env = 0;
// 		while (ft_len_pp((void **)envp[0] + env) > 0)
// 		{
// 			if (!strncmp(envp[0][env], cmd->cmd[com],
// 				ft_strlen(cmd->cmd[com])))
// 				env++;
// 			envp[0][n_env++] = envp[0][env++];
// 		}
// 		envp[0][n_env] = NULL;
// 	}
// 	return (1);
// }
