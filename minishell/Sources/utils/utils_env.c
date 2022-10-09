/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 06:50:45 by tonted            #+#    #+#             */
/*   Updated: 2022/10/09 04:51:26 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_name_in_envp(char **envp, char *name)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (is_name_in_line(envp[i], name))
			return (i);
		i++;
	}
	return (-1);
}

void	put_envp(char *prefix, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		printf("%s%s\n", prefix, envp[i++]);
}

// TODO si PATH n'existes pas?
char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	while (envp[i] && ft_strnstr(envp[i], "PATH=", 5) == 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	cmd = ft_strjoin("/", cmd);
	while (paths[i])
	{
		path = ft_strjoin(paths[i], cmd);
		if (access(path, X_OK) == 0)
		{
			free_null((void *)cmd);
			ft_free_pp((void **)paths);
			return (path);
		}
		free_null((void *)path);
		i++;
	}
	free_null((void *)cmd);
	ft_free_pp((void **)paths);
	return (NULL);
}
