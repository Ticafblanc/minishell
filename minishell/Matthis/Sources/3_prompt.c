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
int    start_minishell(t_global *global)
{
    pid_t     i;

    i = 0;
    signal(SIGINT, monitor_sigint);
    while (global->statut == ON)
    {
        signal(SIGINT, monitor_sigint);
        signal(SIGQUIT, SIG_IGN);
        global->command = readline("Minishell % ");
        if (strnstr(global->command, "test", 4))
        {
            i = fork();
            if (i ==0)
            {
                while (1)
                    printf("coucou");
            }
        }
        if (ft_strnstr(global->command, "exit", 6))
            global->statut = OFF;
    }
    return (0) ;
}


