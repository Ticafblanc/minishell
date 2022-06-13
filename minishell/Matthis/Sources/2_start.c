/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_start.c                                           :+:      :+:    :+:   */
/*   By: sbouras <sbouras@student.42quebec.com>       +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/06/11 18:30:06 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int    start_minishell(t_global *global)
{
    int             i;

    i = 0;
    while (global->statut == ON)
    {
        global->command = readline("Mnishell");
        if (strnstr(global->command, "coucou", 6)
        {
            while (global->command[i])
            {
                ft_putstr(global->command[i]);
                i++;
            }
        }
    }
    return (0) ;
}


