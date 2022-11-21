/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblanco <tblanco@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 05:45:50 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/11/20 12:33:04 by tblanco          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_rev_split(const char **s, char c)
{
	char	*str;
	char	*t_str;
	char	sc[2];

	sc[0] = c;
	sc[1] = '\0';
	if (!s || !*s || !*(s + 1))
		return (ft_substr(*s, 0, ft_str_len((char *)*s) + 1));
	while (*(s + 1))
	{
		t_str = ft_strjoin(*s, sc);
		str = ft_strjoin(t_str, *(s + 1));
		free(t_str);
		s++;
	}
	return (str);
}
