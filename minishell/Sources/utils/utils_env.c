/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 06:50:45 by tonted            #+#    #+#             */
/*   Updated: 2022/09/13 07:14:07 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_name_in_envp(char **envp, char *name)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (is_name_in_line(envp[i], name))
			return (i);
		i++;
	}
	return (-1);
}

void	put_envp(char *prefix, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		printf("%s%s\n",prefix, envp[i++]);
}
