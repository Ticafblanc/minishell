/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblanco <tblanco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:54:28 by tonted            #+#    #+#             */
/*   Updated: 2022/11/23 20:34:22 by tblanco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	push_tab(char **tab, int i, char *str)
{
	int	j;

	if (str)
	{	
		j = i;
		while (tab[j])
			j++;
		tab[j + 1] = NULL;
		while (j > i)
		{
			tab[j] = tab[j - 1];
			j--;
		}
		tab[i] = str;
	}
}

void	add_file(char *flag, t_cmd *cmd, int i_cmd, struct dirent **files)
{
	char	*tmp;

	if (!*flag)
	{
		tmp = cmd->cmd[i_cmd];
		*flag = 0x1;
		cmd->cmd[i_cmd] = ft_strdup((*files)->d_name);
		free_null(tmp);
	}
	else
		push_tab(cmd->cmd, i_cmd, ft_strdup((*files)->d_name));
}

bool	search_files(t_cmd *cmd, int i_cmd)
{
	DIR				*dir;
	struct dirent	*files;
	char			flag;
	char			*pattern;

	pattern = ft_strdup(cmd->cmd[i_cmd]);
	flag = 0x0;
	dir = opendir(getcwd(NULL, 0));
	files = readdir(dir);
	while (files)
	{
		if (strmatch(files->d_name, pattern))
			add_file(&flag, cmd, i_cmd, &files);
		files = readdir(dir);
	}
	closedir(dir);
	free(pattern);
	if (!flag)
		return (false);
	return (true);
}

void	manage_wildcard(t_cmd *cmd)
{
	int				i;

	i = 0;
	while (cmd->cmd[i])
	{
		if (ft_strchr(cmd->cmd[i], '*'))
			search_files(cmd, i);
		i++;
	}
}
