/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1-2-3_execute_builtins.c                           :+:      :+:    :+:   */
/*   By: sbouras <sbouras@student.42quebec.com>       +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/06/13 15:10:10 by jrossign         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

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