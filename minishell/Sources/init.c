/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 08:58:35 by tonted            #+#    #+#             */
/*   Updated: 2022/10/06 11:53:29 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_bin_to_path(char ***envp, char *own_path)
{
	char	*tmp1;
	char	*tmp2;
	int		i;

	i = is_name_in_envp(*envp, "PATH");
	if (i != -1)
	{
		tmp1 = ft_strjoin(get_value((*envp)[i]), ":");
		tmp2 = ft_strjoin(tmp1, own_path);
		free(tmp1);
		free(own_path);
	}
	else
		tmp2 = own_path;
	envp_set_line(envp, tmp2, "PATH");
	free(tmp2);
}

char	*get_own_path(void)
{
	char	*own_path;
	char	*tmp;

	tmp = getcwd(NULL, 0);
	own_path = ft_strjoin(tmp, "/Bin");
	free(tmp);
	tmp = NULL;
	return (own_path);
}

int	init(char ***envp)
{
	char	*own_path;

	own_path = get_own_path();
	*envp = ft_dup_cpp(*envp, ft_len_pp((void **)*envp) + 1);
	if (!find_path("minishell", *envp))
		add_bin_to_path(envp, own_path);
	return (0);
}
