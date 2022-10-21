/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 16:54:56 by tonted            #+#    #+#             */
/*   Updated: 2022/10/21 23:20:18 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_whitespace(int king, char c)
{
	if (king == R_INVISIBLE || king == INVISIBLE)
		if (c == ' ' || (c >= '\t' && c <= '\r'))
			return (true);
	return (false);
}

static bool	is_meta(int king, char c)
{
	if (king == METACHARACTER || king == R_METACHARACTER)
		if (ft_strchr("|&()<>", c) || is_whitespace(INVISIBLE, c))
			return (true);
	return (false);
}

char	check_metacharacter(char **command, int king)
{
	char	i;

	i = 0;
	if (is_whitespace(king, **command) || is_meta(king, **command))
	{
		i = **command;
		if (king == R_INVISIBLE || king == R_METACHARACTER)
		{
			**command = '\0';
			(*command)++;
		}
	}
	else if (king == METACHARACTER)
		(*command)++;
	return (i);
}

char	*remove_quote(char *command)
{
	int		i;
	char	c;
	int		trig;
	char	*new_command;

	i = 0;
	trig = 0;
	new_command = command;
	while (*command != '\0')
	{
		if (!trig && (*command == 34 || *command == 39) && ++i)
		{
			c = *command;
			trig = 1;
		}
		else if (trig && c == *command && ++i)
			trig = 0;
		*command = command[i];
		command++;
	}
	command -= i;
	*command = '\0';
	return (new_command);
}
