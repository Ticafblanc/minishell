/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 09:10:51 by tonted            #+#    #+#             */
/*   Updated: 2022/10/21 23:16:50 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int static	set_flag(char *flags)
{
	int	i;

	i = 1;
	while (flags[i])
	{
		if (flags[i] == 'n')
			i++;
		else
			return (1);
	}
	return (0);
}

int	exec_echo(t_cmd *cmd)
{
	int		flag_n;
	int		i;

	i = 0;
	flag_n = 1;
	if (cmd->cmd[1][i] == '-')
		flag_n = set_flag(cmd->cmd[1]);
	i++;
	if (!flag_n)
		i++;
	while (cmd->cmd[i])
	{
		write(1, remove_quote(cmd->cmd[i]), ft_str_len(cmd->cmd[i]));
		if (cmd->cmd[++i])
			write(1, " ", 1);
	}
	write(1, "\n", flag_n);
	return (1);
}
