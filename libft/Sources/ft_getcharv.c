/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_pp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 13:14:14 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/03/03 10:18:30 by mdoquocb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

int ft_getcharv(void)
{
    static int  i = 0;
    static char buff[BUFSIZ];
    static char *buff_ptr = buff;

    if (i == 0)
    {
        i = read(0, buff, 1);
        buff_ptr = buff;
    }
    if (--i >= 0)
        return  (*buff_ptr++);
    return (EOF);
}
