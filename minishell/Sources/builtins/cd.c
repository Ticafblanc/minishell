/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 09:08:33 by tonted            #+#    #+#             */
/*   Updated: 2022/09/11 09:08:53 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_cd2(char **str, char ***envp)
{
	int		i;

	i = 0;
	while (envp[0][i] && ft_strncmp(envp[0][i], "OLDPWD=", 7) != 0)// gestion de staut pour retour 
		i++;
	if(ft_strncmp(envp[0][i], "OLDPWD=", 7) == 0)
	{
		free(envp[0][i]);
		envp[0][i] = ft_strjoin("OLDPWD=", *str);
		free(*str);
	}
	i = 0;
	while (envp[0][i] && ft_strncmp(envp[0][i], "PWD=", 4) != 0)
		i++;
	if(ft_strncmp(envp[0][i], "PWD=", 4) == 0)
	{
		free(envp[0][i]);
		*str = getcwd(NULL, 0);
		envp[0][i] = ft_strjoin("PWD=", *str);
		free(*str);
	}
	return (1);
}

int	exec_cd(char *dir, char ***envp)
{
	char	*str;
	int		i;

	i = 0;
	if (!dir)
	{
		while (envp[0][i] && ft_strncmp(envp[0][i], "HOME=", 5) != 0)
			i++;
		dir = envp[0][i] + 5;
		i = 0;
	}
	str = getcwd(NULL, 0);
	if (chdir(dir))
		return (perror_minishell(errno, "minishell:"));
	return (exec_cd2(&str, envp));
}