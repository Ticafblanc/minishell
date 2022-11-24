/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 06:50:45 by tonted            #+#    #+#             */
/*   Updated: 2022/11/24 01:22:12 by tonted           ###   ########.fr       */
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

void	put_envp(char *prefix, char **envp, int fd)
{
	int	i;

	i = 0;
	while (envp[i])
		dprintf(fd, "%s%s\n", prefix, envp[i++]);
}

char	*get_path(char *cmd, int i_env, char **envp)
{
	int		i;
	char	*path;
	char	**paths;

	i = 0;
	paths = ft_split(get_value(envp[i_env]), ':');
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

char	*find_path(char *cmd, char **envp)
{
	char	*path;
	int		i_env;

	i_env = is_name_in_envp(envp, "PATH");
	if (i_env == -1)
		return (NULL);
	path = get_path(cmd, i_env, envp);
	if (path)
		return (path);
	return (NULL);
}

char	*find_path_child(char *cmd, char **envp)
{
	char	*path;
	int		i_env;

	i_env = is_name_in_envp(envp, "PATH");
	if (i_env == -1)
		return (ft_strdup(cmd));
	path = get_path(cmd, i_env, envp);
	if (path)
		return (path);
	return (ft_strdup(cmd));
}
