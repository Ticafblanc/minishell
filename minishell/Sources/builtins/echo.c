/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 09:10:51 by tonted            #+#    #+#             */
/*   Updated: 2022/10/17 16:51:55 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_flag(char *flags)
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
		write(1, cmd->cmd[i], ft_str_len(cmd->cmd[i]));
		if (cmd->cmd[++i])
			write(1, " ", 1);
	}
	write(1, "\n", flag_n);
	return (1);
}

/*
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
	tmp2 = cmd->cmd[i];
	cmd->cmd[i] = remove_quote(tmp1);
	free_null(tmp1);
	free_null(tmp2);
	tmp1 = ft_rev_split((const char**)cmd->cmd, ' ');
	cmd->cmd = ft_split(remove_quote(tmp1), ' ');
	return (EXIT_SUCCESS);
*/