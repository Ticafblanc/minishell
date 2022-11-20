/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/11/14 17:04:08 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_next_cmds(t_cmd *cmd);

// void	wait_pipe(t_cmd *cmd)
// {
//   // int status;
//
//   // close(STDOUT_FILENO);
// 	while (cmd->ctrl_op == PIPE)
// 	{
//     // close(STDIN_FILENO);
// 	  // printf("cmd = %s\n", *cmd->cmd);
// 	  // close(cmd->fd[0]);
// 	  // waitpid(cmd->pid, &status, 0);
// 	  // if (WIFEXITED(status) == false)
// 	  //   kill(cmd->pid, SIGKILL);
// 		cmd = cmd->next;
// 	}
// 	printf("cmd = %s\n", *cmd->cmd);
// 	// waitpid(cmd->pid, get_status(), 0);
// }

void	wait_cmd(t_cmd *cmd, int ctrl_op)
{
	if (ctrl_op == HERE_DOC)
	{
		while (cmd)
		{
			waitpid(cmd->pid, get_status(), 0);
			cmd = cmd->next;
		}
	}
}
