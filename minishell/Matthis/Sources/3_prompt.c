/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_start.c                                          :+:      :+:    :+:   */
/*   By: sbouras <sbouras@student.42quebec.com>       +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/06/13 15:10:10 by jrossign         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

//signal(SIGQUIT, SIG_IGN);
void    prompt_minishell(t_global *global)
{
    pid_t     i;

    i = 0;
    signal(SIGABRT, monitor_sigint);
    signal(SIGQUIT, SIG_IGN);
    while (global->statut == ON)
    {
        global->command = readline("Minishell % ");
        if (ft_strnstr(global->command, "exit", 6))
            global->statut = OFF;
    }
    return (0) ;
}


