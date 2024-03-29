/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 09:09:21 by tonted            #+#    #+#             */
/*   Updated: 2022/11/10 11:04:14 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_env(char **envp, int fd)
{
	while (*envp)
	{
		dprintf(fd, "%s\n", *envp);
		envp++;
	}
	return (1);
}
