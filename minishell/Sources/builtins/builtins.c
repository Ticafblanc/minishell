/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 09:02:35 by tonted            #+#    #+#             */
/*   Updated: 2022/11/14 18:41:38 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


//TODO Manage malloc -> strdup all tab at the begin of the manage_arg for
// easier management of free
int	exec_builtins(t_cmd *cmd, char ***envp, int process)
{	
	int	ret;
	int	fd;

	ret = 0;
	fd = cmd->outfile;
	if (cmd->ctrl_op == PIPE && cmd->outfile == STDOUT_FILENO)
		fd = cmd->fd[STDOUT_FILENO];
	manage_args(cmd, *envp);
	if (!ft_strncmp(cmd->cmd[0], "cd", 2))
		ret = exec_cd(cmd->cmd[1], envp);
	else if (!ft_strncmp(cmd->cmd[0], "pwd", 3))
		ret = exec_pwd(fd);
	else if (!ft_strncmp(cmd->cmd[0], "env", 3))
		ret = exec_env(*envp, fd);
	else if (!ft_strncmp(cmd->cmd[0], "echo", 4))
		ret = exec_echo(cmd, fd);
	else if (ft_strncmp(cmd->cmd[0], "export", 6) == 0)
		ret = exec_export(NULL, cmd->cmd, envp, fd);
	else if (ft_strncmp(cmd->cmd[0], "unset", 5) == 0)
		ret = exec_unset(cmd, envp);
	else if (!ft_strncmp(cmd->cmd[0], "exit", 4))
		ret = exec_exit(process, envp, cmd->cmd);
	return (ret);
}
