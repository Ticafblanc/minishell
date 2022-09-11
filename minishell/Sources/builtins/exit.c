/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 09:11:19 by tonted            #+#    #+#             */
/*   Updated: 2022/09/11 09:11:28 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_exit(int process, char ***envp)
{
	if (process == MAIN)
		printf("exit\n");
	ft_free_pp((void **)*envp);
	exit(EXIT_SUCCESS);
	return (0);
}
