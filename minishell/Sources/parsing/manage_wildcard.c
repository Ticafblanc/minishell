/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/21 16:54:28 by tonted            #+#    #+#             */
/*   Updated: 2022/10/21 22:44:32 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO increase when tab > 20.
// TODO push_after not order add.
void	push_tab(char **tab, int i, char (*str)[1024])
{
	int	j;

	if (*str)
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
		tab[i] = *str;
	}
}

bool	strmatch(char *str, char *pattern);

//TODO Manage `.*`
void static	search_files(t_cmd *cmd, int i)
{
	DIR				*dir;
	struct dirent	*files;
	char			flag;
	char			*pattern;

	pattern = cmd->cmd[i];
	flag = 0x0;
	dir = opendir(getcwd(NULL, 0));
	files = readdir(dir);
	while (files)
	{
		if (strmatch(files->d_name, pattern) && files->d_name[0] != '.')
		{
			printf("%s\n", files->d_name);
			if (!flag)
			{
				flag = 0x1;
				cmd->cmd[i] = files->d_name;
			}
			else
				push_tab(cmd->cmd, i, &files->d_name);
		}
		files = readdir(dir);
	}
	closedir(dir);
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
