/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/10/14 02:33:00 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	wait_cmd(t_cmd *cmd, int ctrl_op)
{
	if (ctrl_op == PIPE)
	{
		while (cmd->ctrl_op == PIPE)
		{
			waitpid(cmd->pid, get_at_status(), 0);
			cmd = cmd->next;
		}
		waitpid(cmd->pid, get_at_status(), 0);
	}
	else if (ctrl_op == HERE_DOC)
	{
		while (cmd)
		{
			waitpid(cmd->pid, get_at_status(), 0);
			cmd = cmd->next;
		}
	}
}

void	handle_prompt(int sig_num)
{
	if (sig_num == SIGINT)
	{		
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	handle_exec(int sig_num)
{
	if (sig_num == SIGINT)
		exit(EXIT_FAILURE);
}
