/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_init.c                                           :+:      :+:    :+:   */
/*   By: sbouras <sbouras@student.42quebec.com>       +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/06/13 15:10:10 by jrossign         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	init(char ***envp)
{
	char    *str;
	char    *temp;

	str = getcwd(NULL, 0);
	temp = ft_strjoin(".", str);
	free(str);
	str = ft_strjoin(str, "/Bin/minishell");
	free(temp);
	*envp = ft_dup_cpp(*envp, ft_len_pp((void **)*envp) + 2);
	if (!*envp)
		return (-1);
	envp[0][ft_len_pp((void **)*envp)] = ft_strjoin("SUB=", str);
	// if (!envp[0][ft_len_pp((void **)*envp)])
	//     return (-1);
	//  printf("coiucou\n");
	free(str);
	return (0);
}

int	exec_export(t_cmd *cmd, char ***envp)
{
	char	**export;
	int     i;

	i = 0;
	export = ft_dup_cpp(*envp, ft_len_pp((void **)*envp));
	if (ft_len_pp((void **)cmd->cmd) > 1)
	{
		while (cmd->cmd[++i])
		{
			if (ft_strchr(cmd->cmd[i], '='))
			{
				ft_free_pp((void **)*envp);
				*envp = ft_dup_cpp(export, ft_len_pp((void **)export) + 2);
				envp[0][ft_len_pp((void **) *envp)] = ft_strdup(cmd->cmd[i]);
			}
			ft_free_pp((void **)export);
			if (cmd->cmd[i + 1])
				export = ft_dup_cpp(*envp, ft_len_pp((void **)*envp));
		}
	}
	else
		while (envp[0][i])
			printf("declare -x %s\n", envp[0][i++]);
	return (1);
}

int	exec_unset(t_cmd *cmd, char ***envp)
{
	int		com;
	int		env;
	int		n_env;

	com = 0;
	while (cmd->cmd[++com])
	{
		env = 0;
		n_env = 0;
		while (ft_len_pp((void **)envp[0] + env) > 0 )
		{
			if (!strncmp(envp[0][env], cmd->cmd[com], ft_str_len(cmd->cmd[com])))
				env++;
			envp[0][n_env++] = envp[0][env++];
		}
		envp[0][n_env] = NULL;
	}
	return (1);
}
