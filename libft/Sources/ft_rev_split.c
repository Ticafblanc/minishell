/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 05:45:50 by mdoquocb          #+#    #+#             */
/*   Updated: 2021/10/13 05:46:15 by mdoquocb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_rev_split(const char **s, char c)
{
	char	*str;
	char	*t_str;

	if (!s || !*s)
		return (NULL);
	str = ft_strdup(*s);
	s++;
	while (s && *s)
	{
		t_str = ft_substr(str, 0, ft_str_len(str) + 1);
		free(str);
		t_str[ft_str_len(str)] = c;
		str = ft_strjoin(t_str, *s);
		free(t_str);
		s++;	
	}
	return (str);
}
