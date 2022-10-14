/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   development.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 08:54:18 by tonted            #+#    #+#             */
/*   Updated: 2022/10/14 21:17:10 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_cmd(t_cmd *cmd)
{
	printf("\ncommand a executer\n");
	printf("ctrl_op = %d\n", cmd->ctrl_op);
	// printf("status = %d\n", cmd->status);
	printf("pid = %d\n", cmd->pid);
	printf("cmd [0]= %s\n", cmd->cmd[0]);
	printf("cmd [1]= %s\n", cmd->cmd[1]);
	printf("cmd [2]= %s\n", cmd->cmd[2]);
	printf("cmd [3]= %s\n", cmd->cmd[3]);
	printf("cmd [4]= %s\n", cmd->cmd[4]);
	printf("cmd [5]= %s\n", cmd->cmd[5]);
	//printf("path = %s\n", cmd->path);
	printf("infile = %d\n", cmd->infile);
	printf("outfile = %d\n\n", cmd->outfile);
}
