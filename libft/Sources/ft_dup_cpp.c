/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup_cpp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 13:14:14 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/03/03 10:18:30 by mdoquocb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	**ft_dup_cpp(char **argv, int len_pp)
{
	char	**str;
	int		i;

	i = 0;
	str = (char **)ft_calloc(sizeof(char *), (len_pp + 1));
	if (!str)
		return (NULL);
	while (argv[i])
	{
		str[i] = ft_strdup(argv[i]);
		if (!str[i])
		{
			ft_free_pp((void **)str);
			return (NULL);
		}
		i++;
	}
	str[i] = NULL;
	return (str);
}
