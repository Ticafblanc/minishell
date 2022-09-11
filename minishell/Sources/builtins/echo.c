/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 09:10:51 by tonted            #+#    #+#             */
/*   Updated: 2022/09/11 09:11:01 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_echo(t_cmd *cmd)
{
	int		flag_n;
	int		i;

	i = 0;
	flag_n = 1;
	if (cmd->cmd[1][i] == '-')
		while (cmd->cmd[1][++i])
		{
			if (cmd->cmd[1][i] == 'n')
				flag_n = 0;
			else
			{
				flag_n = 1;
				break;
			}
		}
	i = 1;
	if (!flag_n)
		i++;
	while (cmd->cmd[i])
	{
		write(1, cmd->cmd[i], ft_str_len(cmd->cmd[i]));
		if (cmd->cmd[++i])
			write(1, " ", 1);
	}
	write(1, "\n", flag_n);
	return (1);
}
