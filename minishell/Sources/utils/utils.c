/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/10/14 21:17:32 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	wait_cmd(t_cmd *cmd, int ctrl_op)
{
	if (ctrl_op == PIPE)
	{
		while (cmd->ctrl_op == PIPE)
		{
			if (cmd->fd[STDIN_FILENO] != STDIN_FILENO)
				close(cmd->fd[STDIN_FILENO]);
			if (cmd->fd[STDOUT_FILENO] != STDOUT_FILENO)
				close(cmd->fd[STDOUT_FILENO]);
			if (cmd->infile!= STDIN_FILENO)
				close(cmd->infile);
			if (cmd->outfile != STDOUT_FILENO)
				close(cmd->outfile);
			close(STDIN_FILENO);
			close(STDOUT_FILENO);
			waitpid(cmd->pid, get_status(), 0);
			cmd = cmd->next;
		}
		//waitpid(cmd->pid, get_status(), 0);
	}
	if (ctrl_op == HERE_DOC)
	{
		while (cmd)
		{
			waitpid(cmd->pid, get_status(), 0);
			cmd = cmd->next;
		}
	}
}
