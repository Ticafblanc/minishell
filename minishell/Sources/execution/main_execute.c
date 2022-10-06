/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_execute.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 21:35:20 by tonted            #+#    #+#             */
/*   Updated: 2022/10/06 11:11:42 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	_continue(t_cmd *cmd, char ***envp, int *status, int ctrl)
{
	return (ft_strlen(*cmd->cmd) && !exec_builtins(cmd, status, envp, MAIN) && ((ctrl != AND && ctrl != OR) || ((ctrl == AND && !*status)|| (ctrl == OR && *status))));
}

int	execute(char *command, int *status, char ***envp)
{
	t_cmd	*cmd;
	t_cmd	*r_cmd;
	int		ctrl;

	cmd = NULL;
	ctrl = END;
	*status = 0;
	r_cmd = parsing(command, status, &cmd, *envp);
	while (r_cmd && cmd)
	{
		if (ft_strlen(*cmd->cmd) && exec_pipe(cmd, status, *envp))
			while (cmd->ctrl_op == PIPE)
				cmd = cmd->next;
		else if (_continue(cmd, envp, status, ctrl))
			exec_cmd(cmd, status, *envp, 0);
		ctrl = cmd->ctrl_op;
		cmd = cmd->next;
	}
	if (r_cmd)
		cmd = r_cmd;
	free_cmd(cmd);
	return (*status);
}
