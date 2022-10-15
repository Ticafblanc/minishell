/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   development.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 08:54:18 by tonted            #+#    #+#             */
/*   Updated: 2022/10/14 22:15:16 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	print_cmd(t_cmd *cmd)
// {
// 	printf("\ncommand a executer\n");
// 	printf("cmd [0]= %s\n", cmd->cmd[0]);
// 	printf("cmd [1]= %s\n", cmd->cmd[1]);
// 	printf("cmd [2]= %s\n", cmd->cmd[2]);
// 	printf("ctrl_op = %d\n", cmd->ctrl_op);
// 	// printf("status = %d\n", cmd->status);
// 	printf("pid = %d\n", cmd->pid);
// 	printf("cmd [3]= %s\n", cmd->cmd[3]);
// 	printf("cmd [4]= %s\n", cmd->cmd[4]);
// 	printf("cmd [5]= %s\n", cmd->cmd[5]);
// 	//printf("path = %s\n", cmd->path);
// 	printf("infile = %d\n", cmd->infile);
// 	printf("outfile = %d\n\n", cmd->outfile);
// }

void	print_cmd(t_cmd *cmd)
{
	int	i;

	i = 0;
	printf("\nCommand to execute:");
	while(cmd->cmd[i])
		printf(" %s", cmd->cmd[i++]);
	printf("\n\tctrl_op: %d", cmd->ctrl_op);
	printf("\n\tpid: %d", cmd->pid);
	printf("\n\tinfile: %d", cmd->infile);
	printf("\n\toutfile: %d", cmd->outfile);
	printf("\n\tpath: %s\n\n", cmd->path);
}

void	print_cmds(t_cmd *cmd)
{
	while (cmd)
	{
		print_cmd(cmd);
		cmd = cmd->next;
	}
}