/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 09:02:35 by tonted            #+#    #+#             */
/*   Updated: 2022/10/08 19:46:45 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_builtins(t_cmd *cmd, int *status, char ***envp, int process)
{
	(void) status;
	if (!ft_strncmp(cmd->cmd[0], "cd", 2))
		return (exec_cd(cmd->cmd[1], envp));
	if (!ft_strncmp(cmd->cmd[0], "pwd", 3))
		return (exec_pwd());
	if (!ft_strncmp(cmd->cmd[0], "env", 3))
		return (exec_env(*envp));
	if (!ft_strncmp(cmd->cmd[0], "echo", 4))
		return (exec_echo(cmd));
	if (ft_strncmp(cmd->cmd[0], "export", 6) == 0)
		return (exec_export(NULL, cmd->cmd, envp));
	if (ft_strncmp(cmd->cmd[0], "unset", 5) == 0)
		return (exec_unset(cmd, envp));
	if (!ft_strncmp(cmd->cmd[0], "exit", 4))
		exec_exit(process, envp);
	return (0);
}
