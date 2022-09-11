/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 08:58:35 by tonted            #+#    #+#             */
/*   Updated: 2022/09/11 09:00:38 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*build_envp_line(char *name, char *value);
char	*get_value(char *env_line);
int		is_name_in_envp(char **envp, char *name);
void	envp_set_line(char ***envp, char *value, char *name);

static void	add_bin_to_path(char ***envp)
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

int			init(char ***envp)
{
	*envp = ft_dup_cpp(*envp, ft_len_pp((void **)*envp) + 1);
	add_bin_to_path(envp);
	return (0);
}
