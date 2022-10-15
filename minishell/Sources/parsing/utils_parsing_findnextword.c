/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_findnextword.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:37:03 by tonted            #+#    #+#             */
/*   Updated: 2022/10/15 23:03:46 by tonted           ###   ########.fr       */
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

void	forward_to_end_word(char **s)
{
	while (**s != '\0' && !pass_quote(s) && !ft_strchr(WHITESMETA, **s))
		(*s)++;
}

void	find_next_word(char **command, int *nb_word, char **cmd)
{
	char	*str;

	skip_whitespaces(command);
	str = *command;
	forward_to_end_word(command);
	if (ft_str_len(str) && !ft_strchr(METACHARS, *str))
	{
		*cmd = str;
		(*nb_word)++;
	}
	skip_whitespaces(command);
}

//TODO si str == NULL il faudrait retourner une erreur
char	*find_next_word_redir(char **command)
{
	char	*str;

	skip_whitespaces(command);
	str = *command;
	forward_to_end_word(command);
	if (ft_str_len(str) && !ft_strchr(METACHARS, *str))
		return (str);
	return (NULL);
}