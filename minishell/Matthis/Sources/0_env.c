/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_init.c                                           :+:      :+:    :+:   */
/*   By: sbouras <sbouras@student.42quebec.com>       +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/06/13 15:10:10 by jrossign         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	init(char ***envp)
{
    char    *str;
    char    *temp;

    str = getcwd(NULL, 0);
    temp = ft_strjoin(".", str);
    free(str);
    str = ft_strjoin(str, "/Bin/minishell");
    free(temp);
	*envp = ft_dup_cpp(*envp, ft_len_pp((void **)*envp) + 2);
    if (!*envp)
        return (-1);
    envp[0][ft_len_pp((void **)*envp)] = ft_strjoin("SUB=", str);
    // if (!envp[0][ft_len_pp((void **)*envp)])
    //     return (-1);
    //  printf("coiucou\n");
    free(str);
    return (0);
}