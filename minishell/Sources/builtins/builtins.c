/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblanco <tblanco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 09:02:35 by tonted            #+#    #+#             */
/*   Updated: 2022/11/23 21:04:31 by tblanco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char *s)
{
	int			i;
	static char	list[8][8]
		= {"cd", "pwd", "env", "echo", "export", "unset", "exit"};

	i = 0;
	while (i < 7)
	{
		if (!strncmp(s, list[i], ft_str_len(list[i])))
			return (true);
		i++;
	}
	return (false);
}

void	free_args(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free_null(tab[i]);
		i++;
	}
}

int	manage_builtins(t_cmd *cmd, char ***envp, int process, int fd)
{
	if (!ft_strncmp(cmd->cmd[0], "cd", 2))
		return (exec_cd(cmd->cmd[1], envp));
	else if (!ft_strncmp(cmd->cmd[0], "pwd", 3))
		return (exec_pwd(fd));
	else if (!ft_strncmp(cmd->cmd[0], "env", 3))
		return (exec_env(*envp, fd));
	else if (!ft_strncmp(cmd->cmd[0], "echo", 4))
		return (exec_echo(cmd, fd));
	else if (ft_strncmp(cmd->cmd[0], "export", 6) == 0)
		return (exec_export(NULL, cmd->cmd, envp, fd));
	else if (ft_strncmp(cmd->cmd[0], "unset", 5) == 0)
		return (exec_unset(cmd, envp));
	else if (!ft_strncmp(cmd->cmd[0], "exit", 4))
		return (exec_exit(process, envp, cmd));
	return (0);
}

int	exec_builtins(t_cmd *cmd, char ***envp, int process)
{	
	int	ret;
	int	fd;

	if (!cmd->cmd[0] || cmd->flag & F_BRACE || !is_builtin(cmd->cmd[0]))
		return (0);
	ret = 0;
	fd = cmd->outfile;
	if (cmd->ctrl_op == PIPE && cmd->outfile == STDOUT_FILENO)
		fd = cmd->fd[STDOUT_FILENO];
	manage_args(cmd, *envp);
	ret = manage_builtins(cmd, envp, process, fd);
	return (ret);
}
