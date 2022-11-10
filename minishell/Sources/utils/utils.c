/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/11/10 17:33:13 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_cmd	*wait_pipe(t_cmd *cmd)
{
	while (cmd->ctrl_op == PIPE)
	{
		if (cmd->fd[STDIN_FILENO] != STDIN_FILENO)
			close(cmd->fd[STDIN_FILENO]);
		if (cmd->fd[STDOUT_FILENO] != STDOUT_FILENO)
			close(cmd->fd[STDOUT_FILENO]);
		if (cmd->infile != STDIN_FILENO)
			close(cmd->infile);
		if (cmd->outfile != STDOUT_FILENO)
			close(cmd->outfile);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		waitpid(cmd->pid, get_status(), 0);
		cmd = cmd->next;
	}
	return (cmd);
}

void	wait_cmd(t_cmd *cmd, int ctrl_op)
{
	if (ctrl_op == PIPE)
		cmd = wait_pipe(cmd);
	if (ctrl_op == HERE_DOC)
	{
		while (cmd)
		{
			waitpid(cmd->pid, get_status(), 0);
			cmd = cmd->next;
		}
	}
}
