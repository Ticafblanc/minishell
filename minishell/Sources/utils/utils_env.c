/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblanco <tblanco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 06:50:45 by tonted            #+#    #+#             */
/*   Updated: 2022/11/23 22:08:47 by tblanco          ###   ########.fr       */
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

char	*find_path(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	if (is_name_in_envp(envp, "PATH") == -1)
		return (NULL);
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

char	*find_path_child(char *cmd, char **envp)
{
	char	**paths;
	char	*path;
	int		i;

	i = 0;
	if (is_name_in_envp(envp, "PATH") == -1)
		return (ft_strdup(cmd));
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
	ft_free_pp((void **)paths);
	return (cmd);
}
