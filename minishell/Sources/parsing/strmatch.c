/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strmatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:33:50 by tonted            #+#    #+#             */
/*   Updated: 2022/10/22 19:11:02 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int static	**init_matrix_tab(int len_str, int len_pat)
{
	int	i_str;
	int	i_pat;
	int	**tab;

	i_str = 0;
	tab = (int **)malloc(sizeof(int *) * (len_str + 1));
	while (i_str <= len_str)
	{
		i_pat = 0;
		tab[i_str] = (int *)malloc(sizeof(int) * (len_pat + 1));
		while (i_pat <= len_pat)
			tab[i_str][i_pat++] = false;
		i_str++;
	}
	i_str = 0;
	tab[0][0] = true;
	return (tab);
}

void static	set_first_line(int len_str, int len_pat, char *pattern, int **tab)
{
	int	i;

	i = 1;
	while (i <= len_str && i <= len_pat)
	{
		if (pattern[i - 1] == '*')
			tab[0][i] = tab[0][i - 1];
		i++;
	}
}

void static	set_all_tab(char *pattern, char *str, int **tab)
{
	int	c;
	int	r;
	int	len_str;
	int	len_pat;

	len_str = ft_strlen(str);
	len_pat = ft_strlen(pattern);
	c = 1;
	while (c <= len_str)
	{
		r = 0;
		while (++r <= len_pat && pattern[r - 1])
		{
			if (pattern[r - 1] == '*')
			{
				if (tab[c][r - 1])
					tab[c][r] = tab[c][r - 1];
				else if (tab[c - 1][r])
					tab[c][r] = tab[c - 1][r];
			}
			else if (pattern[r - 1] == str[c - 1])
				tab[c][r] = tab[c - 1][r - 1];
		}
		c++;
	}
}

void static	free_tab_int(int **tab, int len)
{
	while (len)
		free(tab[--len]);
	free(tab);
}

/*
	returns true if the pattern matchs with the string, otherwise return false
*/
bool	strmatch(char *str, char *pattern)
{
	int		len_str;
	int		len_pat;
	int		**tab;
	bool	ret;
	int		i;

	if (str[0] == '.' && pattern[0] != '.')
		return (false);
	len_str = ft_strlen(str);
	len_pat = ft_strlen(pattern);
	tab = init_matrix_tab(len_str, len_pat);
	set_first_line(len_str, len_pat, pattern, tab);
	set_all_tab(pattern, str, tab);
	ret = (bool)tab[len_str][len_pat];
	free_tab_int(tab, len_str + 1);
	return (ret);
}
