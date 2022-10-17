/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_var.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 17:18:58 by tonted            #+#    #+#             */
/*   Updated: 2022/10/17 17:25:24 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	forward_to_next(char *s, int i, char c)
{
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

int	interpret_var(t_cmd *cmd, char **envp, int i, int i_s)
{
	int		i_end;
	int		i_env;
	char	*tmp1;
	char	*tmp2;

	cmd->cmd[i][i_s] = '\0';
	i_end = forward_to_next(cmd->cmd[i], i_s + 1, ' ');
	cmd->cmd[i][i_end] = '\0';
	i_env = is_name_in_envp(envp, &cmd->cmd[i][i_s + 1]);
	if (i_env == -1)
		tmp1 = "";
	else
		tmp1 = get_value(envp[i_env]);
	tmp2 = ft_strjoin(cmd->cmd[i], tmp1);
	cmd->cmd[i][i_s] = ' ';
	tmp1 = ft_strjoin(tmp2, &cmd->cmd[i][i_end]);
	free_null(tmp2);
	free_null(cmd->cmd[i]);
	cmd->cmd[i] = remove_quote(tmp1);
	tmp2 = ft_rev_split((const char **)cmd->cmd, ' ');
	cmd->cmd = ft_split(remove_quote(tmp2), ' ');
	return (EXIT_SUCCESS);
}

char	**manage_var(t_cmd *cmd, char **envp)
{
	int		i;
	int		i_s;

	i = 0;
	while (cmd->cmd[i])
	{
		i_s = 0;
		while (cmd->cmd[i][i_s])
		{
			if (cmd->cmd[i][i_s] == '\'')
				i_s = forward_to_next(cmd->cmd[i], i_s++, '\'');
			else if (cmd->cmd[i][i_s] == '$')
			{
				i_s = interpret_var(cmd, envp, i, i_s);
				continue ;
			}
			i_s++;
		}
		i++;
	}
	return (cmd->cmd);
}
