/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 09:18:47 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/02/05 13:59:38 by mdoquocb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

<<<<<<<< HEAD:libft/Sources/2-2-3_execute_builtins.c
#include <minishell.h>
	
//if (ft_strnstr(g_global.command, "exit", 6)) // a ajouter au parsinng 
		// g_global.statut = EXIT_SUCCESS; // a ajouter au parsinng

int	exec_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	printf("%s\n", buf);
	free(buf);
	return (0);
}
========
#include <libft.h>

int	ft_memlen(unsigned long n)
{
	int	len;

	len = 0;
	if (n / 16 > 0)
		len += ft_memlen(n / 16);
	len++;
	return (len);
}
>>>>>>>> origin/ours🧸:libft/Sources/ft_memlen.c
