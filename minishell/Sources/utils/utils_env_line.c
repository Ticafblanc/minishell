/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblanco <tblanco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 07:10:34 by tonted            #+#    #+#             */
/*   Updated: 2022/11/20 12:49:52 by tblanco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_name(char *env_line)
{
	int	i;

	i = 0;
	while (env_line[i])
	{
		if (env_line[i] == '=')
		{
			env_line[i] = '\0';
			return (env_line);
		}
		i++;
	}
	return (NULL);
}

char	*get_value(char *env_line)
{
	int		i;

	i = 0;
	while (env_line[i] != '=' && env_line[i])
		i++;
	if (!env_line[++i])
		return ("");
	return (&env_line[i]);
}

int	is_name_in_line(char *envline, char *name)
{
	int	len;

	len = ft_strlen(name);
	if (!ft_strncmp(envline, name, len) && envline[len] == '=')
		return (1);
	return (0);
}

static char	*build_envp_line(char *name, char *value)
{
	char	*line;
	char	*tmp;

	tmp = ft_strjoin(name, "=");
	line = ft_strjoin(tmp, value);
	free(tmp);
	return (line);
}

void	envp_set_line(char ***envp, char *value, char *name)
{
	char	*line;
	int		i_name;

	(void) envp;
	if (!name)
		return ;
	line = build_envp_line(name, value);
	i_name = is_name_in_envp(*envp, name);
	if (i_name == -1)
		add_line_tabstr(envp, line);
	else
	{
		free((*envp)[i_name]);
		(*envp)[i_name] = line;
	}
}
