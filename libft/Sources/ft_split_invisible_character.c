/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_invisible_character.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 05:45:50 by mdoquocb          #+#    #+#             */
/*   Updated: 2021/10/13 05:46:15 by mdoquocb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static int	count(char *command)
{
	size_t	st;
	int		trigger;

	st = 0;
	trigger = 0;
	while (*command)
	{
		if (!check_invisible_characters(*command) && trigger == 0)
		{
			trigger = 1;
			st++;
		}
		else if (check_invisible_characters(*command))
		{
			while (check_invisible_characters(*command))
				command++;
			command--;
			trigger = 0;
		}	
		command++;
	}
	return (st);
}

char	**ft_split_invisible_character(char *command)
{
	size_t	st;
	size_t	st2;
	int		i;
	char	**str;

	if (!command)
		return (NULL);
	str = (char **)ft_calloc((count(command) + 1), sizeof(char *));
	if (!str)
		return (NULL);
	st = -1;
	st2 = 0;
	i = -1;
	while (++st <= ft_strlen(command))
	{
		if (!check_invisible_characters(command[st]) && i < 0)
			i = st;
		else if (i >= 0 && (check_invisible_characters(command[st])
				|| st == ft_strlen(command)))
		{
			str[st2++] = ft_substr(command, i, (st - i));
			i = -1;
		}
	}
	return (str);
}
