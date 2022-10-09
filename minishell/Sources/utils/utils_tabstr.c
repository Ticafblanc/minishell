/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tabstr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 06:52:34 by tonted            #+#    #+#             */
/*   Updated: 2022/10/08 19:37:14 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_line_tabstr(char ***tabstr, char *line)
{
	char	**new_tabstr;
	int		i;

	new_tabstr = (char **)malloc(sizeof(char *) * (ft_len_pp((void **)*tabstr)
				+ 2));
	i = 0;
	while ((*tabstr)[i])
	{
		new_tabstr[i] = (*tabstr)[i];
		i++;
	}
	new_tabstr[i++] = line;
	new_tabstr[i] = NULL;
	free(*(tabstr));
	*(tabstr) = new_tabstr;
}

char	**get_alpha_tabstr(char **tabstr)
{
	char	**n_tabstr;
	char	*temp;
	int		i;
	int		j;

	n_tabstr = tabstrdup(tabstr);
	i = 0;
	while (n_tabstr[i])
	{
		j = i + 1;
		while (n_tabstr[j])
		{
			if (ft_strcmp(n_tabstr[i], n_tabstr[j]) > 0)
			{
				temp = ft_strdup(n_tabstr[i]);
				n_tabstr[i] = ft_strdup(n_tabstr[j]);
				n_tabstr[j] = ft_strdup(temp);
			}
			j++;
		}
		i++;
	}
	return (n_tabstr);
}

char	**tabstrdup(char **tabstr)
{
	char	**n_tabstr;
	int		i;

	n_tabstr = (char **)malloc(sizeof(char *) * (ft_len_pp((void **)tabstr)
				+ 1));
	i = 0;
	while (*tabstr)
		n_tabstr[i++] = ft_strdup(*tabstr++);
	n_tabstr[i] = NULL;
	return (n_tabstr);
}
