/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblanco <tblanco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 21:35:20 by tonted            #+#    #+#             */
/*   Updated: 2022/11/23 20:35:13 by tblanco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	_continue(t_cmd *cmd, char ***envp, int ctrl)
{
	return (ft_strlen(*cmd->cmd) && !exec_builtins(cmd, envp, MAIN)
		&& ((ctrl != AND && ctrl != OR)
			|| ((ctrl == AND && !get_value_status())
				|| (ctrl == OR && get_value_status()))));
}

int	execute(char *command, char ***envp)
{
	t_cmd	*cmd;
	t_cmd	*r_cmd;
	int		ctrl;

	cmd = NULL;
	ctrl = END;
	set_status(0);
	r_cmd = parsing(command, &cmd, *envp);
	while (cmd && get_value_status() != QNC)
	{
		if (exec_pipe(cmd, *envp))
			while (cmd->ctrl_op == PIPE)
				cmd = cmd->next;
		else if (_continue(cmd, envp, ctrl))
			exec_cmd(cmd, *envp, 0);
		ctrl = cmd->ctrl_op;
		cmd = cmd->next;
	}
	free_next_cmds(r_cmd);
	return (get_value_status());
}
