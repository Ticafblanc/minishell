/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 21:21:15 by tonted            #+#    #+#             */
/*   Updated: 2022/10/08 19:38:17 by tonted           ###   ########.fr       */
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

void	free_cmd(t_cmd *cmd)
{
	t_cmd	*t_cmd;

	while (cmd)
	{
		t_cmd = cmd;
		if (cmd)
			free(cmd);
		cmd = t_cmd->next;
	}
}
