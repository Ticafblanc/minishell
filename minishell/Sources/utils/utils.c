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
			waitpid(cmd->pid, get_status(), 0);
			cmd = cmd->next;
		}
		waitpid(cmd->pid, get_status(), 0);
	}
	else if (ctrl_op == HERE_DOC)
	{
		while (cmd)
		{
			waitpid(cmd->pid, get_status(), 0);
			cmd = cmd->next;
		}
	}
}
