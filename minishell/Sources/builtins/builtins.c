/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 09:02:35 by tonted            #+#    #+#             */
/*   Updated: 2022/11/09 09:34:32 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	manage_args(t_cmd *cmd, char **envp);
void	manage_argv2(t_cmd *cmd, char **envp);

int	exec_builtins(t_cmd *cmd, char ***envp, int process)
{	
	int ret;

	ret = 0;
	manage_args(cmd, *envp);
	if (!ft_strncmp(cmd->cmd[0], "cd", 2))
		ret = exec_cd(cmd->cmd[1], envp);
	else if (!ft_strncmp(cmd->cmd[0], "pwd", 3))
		ret = exec_pwd();
	else if (!ft_strncmp(cmd->cmd[0], "env", 3))
		ret = exec_env(*envp);
	else if (!ft_strncmp(cmd->cmd[0], "echo", 4))
		ret = exec_echo(cmd);
	else if (ft_strncmp(cmd->cmd[0], "export", 6) == 0)
		ret = exec_export(NULL, cmd->cmd, envp);
	else if (ft_strncmp(cmd->cmd[0], "unset", 5) == 0)
		ret = exec_unset(cmd, envp);
	else if (!ft_strncmp(cmd->cmd[0], "exit", 4))
		ret = exec_exit(process, envp, cmd->cmd);
	// TODO free if malloced!
	return (ret);
}
