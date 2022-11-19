/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 05:45:50 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/11/11 00:48:48 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_rev_split(const char **s, char c)
{
	char	*str;
	char	*t_str;

	if (!s || !*s || !*s + 1)
		return (ft_substr(*s, 0, ft_str_len((char *)*s) + 1));
	while (*(s + 1))
	{
		t_str = ft_strjoin(*s, &c);
		str = ft_strjoin(t_str, *(s + 1));
		free(t_str);
		s++;
	}
	return (str);
}
