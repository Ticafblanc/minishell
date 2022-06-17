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

extern t_global g_global;

static int  check_empty_line(char *command)
{
    int i;

    i = 0;
    if (!command)
    {
        g_global.statut = EXIT_SUCCESS;
        return (0);
    }
    while (command[i])
    {
        if ((command[i] < 9 || command[i] > 13) && command[i] != 32)
            return (1);
        else
            i++;
    }
    return (0);
}

void    prompt_minishell(void)
{
    g_global.command = readline("Minishell % ");
    if (check_empty_line(g_global.command))
        add_history(g_global.command);
    if (ft_strnstr(g_global.command, "exit", 6))// a ajouter au parsinng 
            g_global.statut = EXIT_SUCCESS;// a ajouter au parsinng
}



