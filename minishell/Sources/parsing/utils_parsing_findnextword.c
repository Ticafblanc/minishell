/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_findnextword.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:37:03 by tonted            #+#    #+#             */
/*   Updated: 2022/10/13 18:09:09 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	skip_whitespaces(char **s)
{
	while (**s && ft_strchr(WHITESPACES, **s))
	{
		**s = '\0';
		(*s)++;
	}
}

void	forward_to_end_word(char **s, int *status)
{
	while (**s != '\0' && !pass_quote(s, status) && !ft_strchr(WHITESMETA, **s))
		(*s)++;
}

void	find_next_word(char **command, int *status, int *nb_word, char **cmd)
{
	char	*str;

	skip_whitespaces(command);
	str = *command;
	forward_to_end_word(command, status);
	if (ft_str_len(str))
	{
		*cmd = str;
		(*nb_word)++;
	}
	skip_whitespaces(command);
}
