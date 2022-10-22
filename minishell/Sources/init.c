/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/11 08:58:35 by tonted            #+#    #+#             */
/*   Updated: 2022/10/21 22:15:19 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define PATH "PATH"
#define SEP_PATH ":"
#define FOLDER_BIN "/Bin"
#define BIN "minishell"

static void	add_bin_to_path(char ***envp, char *own_path)
{
	char	*tmp1;
	char	*tmp2;
	int		i_path;

	i_path = is_name_in_envp(*envp, PATH);
	if (i_path != -1)
	{
		tmp1 = ft_strjoin(get_value((*envp)[i_path]), SEP_PATH);
		tmp2 = ft_strjoin(tmp1, own_path);
		envp_set_line(envp, tmp2, PATH);
		free_null((void *)tmp1);
		free_null((void *)tmp2);
	}
	else
		envp_set_line(envp, own_path, PATH);
}

static char	*get_own_path(void)
{
	char	*own_path;
	char	*tmp;

	tmp = getcwd(NULL, 0);
	own_path = ft_strjoin(tmp, FOLDER_BIN);
	free_null((void *)tmp);
	return (own_path);
}

int	init(char ***envp)
{
	char	*own_path;
	char	*tmp;

	own_path = get_own_path();
	*envp = ft_dup_cpp(*envp, ft_len_pp((void **)*envp) + 1);
	tmp = find_path(BIN, *envp);
	if (!tmp)
		add_bin_to_path(envp, own_path);
	free_null(own_path);
	free_null(tmp);
	return (EXIT_SUCCESS);
}
