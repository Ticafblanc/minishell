/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildecard.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 16:33:50 by tonted            #+#    #+#             */
/*   Updated: 2022/10/19 16:34:13 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool wildcard(char *str, char *pattern)  
{  
	int	i_str;
	int	i_pat;
	int len_str = ft_strlen(str);
	int len_pat = ft_strlen(pattern);
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
	i_str = 1;
	while (i_str <= len_str && i_str <= len_pat)
	{
		if (pattern[i_str - 1] == '*')
			tab[0][i_str] = tab[0][i_str - 1];
		i_str++;
	}
	i_str = 1;
	while (i_str <= len_str)
	{
		i_pat = 1;
		while (i_pat <= len_pat && pattern[i_pat - 1])
		{
			if (pattern[i_pat - 1] == '*')
				tab[i_str][i_pat] = tab[i_str][i_pat - 1] || tab[i_str - 1][i_pat];
			else if (pattern[i_pat - 1] == str[i_str - 1])
				tab[i_str][i_pat] =  tab[i_str - 1][i_pat - 1];	
			i_pat++;
		}
		i_str++;
	}
	return (tab[len_str][len_pat]);  
}  