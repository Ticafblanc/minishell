/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 21:35:20 by tonted            #+#    #+#             */
/*   Updated: 2022/10/14 02:39:20 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO refactor `get_status()`
static bool	_continue(t_cmd *cmd, char ***envp, int ctrl)
{
	return (ft_strlen(*cmd->cmd) && !exec_builtins(cmd, envp, MAIN)
		&& ((ctrl != AND && ctrl != OR)
			|| ((ctrl == AND && !get_status()) || (ctrl == OR && get_status()))));
}

//TODO explications sur le ctrl?
//TODO a quoi correspond r_cmd?
int	execute(char *command, char ***envp)
{
	t_cmd	*cmd;
	t_cmd	*r_cmd;
	int		ctrl;

	cmd = NULL;
	ctrl = END;
	set_status(0);
	r_cmd = parsing(command, &cmd, *envp);
	while (r_cmd && cmd)
	{
		if (ft_strlen(*cmd->cmd) && exec_pipe(cmd, *envp))
			while (cmd->ctrl_op == PIPE)
				cmd = cmd->next;
		else if (_continue(cmd, envp, ctrl))
			exec_cmd(cmd, *envp, 0);
		ctrl = cmd->ctrl_op;
		cmd = cmd->next;
	}
	if (r_cmd)
		cmd = r_cmd;
	free_cmd(cmd);
	return (get_status());
}
