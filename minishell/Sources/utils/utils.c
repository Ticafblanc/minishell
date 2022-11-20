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

void	wait_pipe(t_cmd *cmd)
{
	while (cmd->ctrl_op == PIPE)
	{
	  printf("cmd = %s\n", *cmd->cmd);
		if (cmd->fd[STDIN_FILENO] != STDIN_FILENO)
			close(cmd->fd[STDIN_FILENO]);
		if (cmd->fd[STDOUT_FILENO] != STDOUT_FILENO)
			close(cmd->fd[STDOUT_FILENO]);
	  //close(STDIN_FILENO);
	  //close(STDOUT_FILENO);
	  printf("cmd = %s\n", *cmd->cmd);
		cmd = cmd->next;
	}
	//close(STDIN_FILENO);
	//close(STDOUT_FILENO);
	printf("cmd = %s\n", *cmd->cmd);
	waitpid(cmd->pid, get_status(), 0);
}

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
