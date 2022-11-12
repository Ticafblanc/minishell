/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing_findnextword.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 16:37:03 by tonted            #+#    #+#             */
/*   Updated: 2022/11/11 23:00:06 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	pass_quote(char **command)
{
	int	i;

	i = 0;
	if ((**command == 34 || **command == 39))
	{
		while (command[0][i++] != '\0')
		{
			if (command[0][i] == '\0')
			{
				set_status(perror_minishell(QNC, *command));
				return (get_value_status());
			}
			if (**command == command[0][i])
			{
				*command += ++i;
				break ;
			}
		}
	}
	return (0);
}

static void	skip_whitespaces(char **s)
{
	while (**s && ft_strchr(WHITESPACES, **s))
	{
		**s = '\0';
		(*s)++;
	}
}

static void	forward_to_end_word(char **s)
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
