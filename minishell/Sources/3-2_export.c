/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3-2_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 17:51:13 by tonted            #+#    #+#             */
/*   Updated: 2022/09/10 18:05:41 by tonted           ###   ########.fr       */
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

int		ft_export(char *pathname, char **args, char ***envp)
{
	(void)	pathname;
	(void)	args;
	(void)	envp;

	print_envp_alpha(*envp);

	return (1);
}