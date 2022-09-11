/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3-2_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 17:51:13 by tonted            #+#    #+#             */
/*   Updated: 2022/09/10 20:13:34 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_envp(char *prefix, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		printf("%s%s\n",prefix, envp[i++]);
}

void	ft_freetabstr(char **tab)
{
	int	i;

	if (*tab)
	{
		i = 0;
		while ((tab)[i])
			free((tab)[i++]);
		free(tab);
		tab = NULL;
	}
}

char	**tabstrdup(char **envp)
{
	char	**env;
	int		i;

	env = (char **)malloc(sizeof(char *) * (ft_len_pp((void **)envp) + 1));
	i = 0;
	while (*envp)
		env[i++] = ft_strdup(*envp++);
	env[i] = NULL;
	return (env);
}

int		ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *) s1 - *(unsigned char *) s2);
}

char	**get_alpha_envp(char **envp)
{
	char 	**n_envp;
	char	*temp;
	int		i;
	int		j;
	
	n_envp = tabstrdup(envp);
	i = 0;
	while (n_envp[i])
	{
		j = i + 1;
		while (n_envp[j])
		{
			if (ft_strcmp(n_envp[i], n_envp[j]) > 0)
			{
				temp = ft_strdup(n_envp[i]);
				n_envp[i] = ft_strdup(n_envp[j]);
				n_envp[j] = ft_strdup(temp);
			}
			j++;
		}
		i++;
	}
	return n_envp;
}

void	print_envp_alpha(char **env)
{
	char	**env_alpha;

	env_alpha = get_alpha_envp(env);
	put_envp("declare -x ", env_alpha);
	ft_freetabstr(env_alpha);

}

char	*get_name(char *env_line)
{
	int	i;

	i = 0;
	while (env_line[i])
	{
		if(env_line[i] == '=')
			env_line[i] = '\0';
		i++;
	}
	return (env_line);
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

char	*build_envp_line(char *name, char *value)
{
	char	*line;
	char	*tmp;

	tmp = ft_strjoin(name, "=");
	line = ft_strjoin(tmp, value);
	free(tmp);
	return (line);
}

int	is_name_in_line(char *envline, char *name)
{
	int	len;

	len = ft_strlen(name);
	if (!ft_strncmp(envline, name, len) && envline[len] == '=')
		return (1);
	return (0);
}

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

void	envp_set_line(char ***envp, char *value, char *name)
{
	(void)	envp;
	char	*line;
	int		i_name;

	line = build_envp_line(name, value);
	i_name = is_name_in_envp(*envp, name);
	if (i_name == -1)
		printf("add line to envp\n");
	else
	{
		printf("replace line %d (%s)\n", i_name, line);
	}
}

int		ft_export(char *pathname, char **args, char ***envp)
{
	(void)	pathname;
	(void)	args;
	(void)	envp;
	int		i;
	
	if (ft_len_pp((void **)args) > 1)
	{
		i = 1;
		while (args[i])
		{
			envp_set_line(envp, get_value(args[i]), get_name(args[i]));
			i++;
		}
	}
	else
		print_envp_alpha(*envp);

	return (1);
}