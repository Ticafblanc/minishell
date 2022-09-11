/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3-1_builtins.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/09/10 17:54:12 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	exec_echo(t_cmd *cmd)
{
	int		flag_n;
	int		i;

	i = 0;
	flag_n = 1;
	if (cmd->cmd[1][i] == '-')
		while (cmd->cmd[1][++i])
		{
			if (cmd->cmd[1][i] == 'n')
				flag_n = 0;
			else
			{
				flag_n = 1;
				break;
			}
		}
	i = 1;
	if (!flag_n)
		i++;
	while (cmd->cmd[i])
	{
		write(1, cmd->cmd[i], ft_str_len(cmd->cmd[i]));
		if (cmd->cmd[++i])
			write(1, " ", 1);
	}
	write(1, "\n", flag_n);
	return (1);
}

int	exec_exit(int process, char ***envp)
{
	if (process == MAIN)
		printf("exit\n");
	ft_free_pp((void **)*envp);
	exit(EXIT_SUCCESS);
	return (0);
}

int	exec_builtins2(t_cmd *cmd, int *status, char ***envp, int process)
{
	if (envp)

	if (status)

	if (!ft_strncmp(cmd->cmd[0], "echo", 4))
		return (exec_echo(cmd));
	if (ft_strncmp(cmd->cmd[0], "export", 6) == 0)
		return (ft_export(NULL ,cmd->cmd, envp));
	// if (ft_strncmp(cmd->cmd[0], "export", 6) == 0)
	// 	return (exec_export(cmd, envp));
	if (ft_strncmp(cmd->cmd[0], "unset", 5) == 0)
		return (exec_unset(cmd, envp));
	if (!ft_strncmp(cmd->cmd[0], "exit", 4))
		exec_exit(process, envp);
	return (0);
	
}