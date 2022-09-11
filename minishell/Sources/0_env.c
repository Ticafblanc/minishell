/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/09/11 07:35:56 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*build_envp_line(char *name, char *value);
char	*get_value(char *env_line);
int		is_name_in_envp(char **envp, char *name);
void	envp_set_line(char ***envp, char *value, char *name);

void	add_bin_to_path(char ***envp)
{
	char	*tmp1;
	char	*tmp2;
	char	*tmp3;
	int		i;

	tmp1 = getcwd(NULL, 0);
	tmp2 = ft_strjoin(tmp1, "/Bin");
	free(tmp1);
	tmp1 = NULL;
	i = is_name_in_envp(*envp, "PATH");
	if (i != -1)
	{
		tmp1 = ft_strjoin(get_value((*envp)[i]), ":");
		tmp3 = ft_strjoin(tmp1, tmp2);
		free(tmp1);
		free(tmp2);
	}
	else
		tmp3 = tmp2;
	envp_set_line(envp, tmp3, "PATH");
	free(tmp3);
}

int	init(char ***envp)
{
	*envp = ft_dup_cpp(*envp, ft_len_pp((void **)*envp) + 1);
	add_bin_to_path(envp);
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
