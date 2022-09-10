/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3-2_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 17:51:13 by tonted            #+#    #+#             */
/*   Updated: 2022/09/10 17:55:23 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_export(char *pathname, char **args, char ***envp)
{
	(void)	pathname;
	(void)	args;
	(void)	envp;

	printf("Hey ft_export!!!\n");

	return (1);
}