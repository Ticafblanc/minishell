/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tonted <tonted@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 08:38:28 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/10/31 18:51:06 by tonted           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

size_t	ft_strlen(const char *maxlen)
{
	unsigned int	count;

	count = 0;
	if (maxlen)
	{
		count = 0;
		while (maxlen[count])
			count++;
	}
	return (count);
}
