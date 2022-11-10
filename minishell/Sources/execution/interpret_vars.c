/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 18:02:06 by tonted            #+#    #+#             */
/*   Updated: 2022/11/11 00:43:33 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	malloc_cmds(t_cmd *cmd)
{
	int	i;

	i = 0;
	cmd->malloced = 0x1;
	while (cmd->cmd[i])
	{
		cmd->cmd[i] = ft_strdup(cmd->cmd[i]);
		i++;
	}
}

static int	interpret_var(char **s, int i, char **envp)
{
	int		i_end;
	int		i_env;
	char	c_tmp;
	char	*tmp1;
	char	*tmp2;

	i_end = 1 + i;
	while (ft_isalnum((*s)[i_end]))
		i_end++;
	c_tmp = (*s)[i_end];
	(*s)[i_end] = '\0';
	i_env = is_name_in_envp(envp, &(*s)[i + 1]);
	if (i_env == -1)
		tmp1 = "";
	else
		tmp1 = get_value(envp[i_env]);
	(*s)[i] = '\0';
	tmp2 = ft_strjoin(*s, tmp1);
	(*s)[i_end] = c_tmp;
	tmp1 = ft_strjoin(tmp2, &(*s)[i_end]);
	i = ft_strlen(tmp2);
	free(tmp2);
	(*s) = tmp1;
	return (i);
}

static int	interpret_status(t_cmd *cmd, char **envp, int i, int i_s)
{
	char	*tmp1;

	(void)envp;
	cmd->cmd[i][i_s] = '\0';
	tmp1 = ft_strjoin(cmd->cmd[i], ft_itoa(*last_status()));
	cmd->cmd[i] = ft_strjoin(tmp1, &cmd->cmd[i][i_s]);
	free_null(tmp1);
	return (EXIT_SUCCESS);
}

void	interpret_vars(t_cmd *cmd, int i, int i_cmd, char **envp)
{
	if (!cmd->malloced)
		malloc_cmds(cmd);
	if (cmd->cmd[i_cmd][i + 1] == '?')
		i = interpret_status(cmd, envp, i_cmd, i);
	else
		i = interpret_var(&cmd->cmd[i_cmd], i, envp);
}
