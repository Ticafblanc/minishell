/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_parsing.c                                        :+:      :+:    :+:   */
/*   By: sbouras <sbouras@student.42quebec.com>       +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/06/13 15:10:10 by jrossign         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_global	g_global;

static void check_nb_command(void);
{
    int i;
    
    i = 0;
    g_global.nb_command = 0;
    while (g_global.command[i])
    {
        while (g_global.command[i] && g_global.command[i] == 32
            || (g_global.command[i] >= 9 && g_global.command[i] <= 13))
            i++;
        if (g_global.command[i] && g_global.command[i] != 32
            && (g_global.command[i] <= 9 || g_global.command[i] >= 13))
            {
                g_global.nb_command++;
                while (g_global.command[i] && g_global.command[i] != 32
                    && (g_global.command[i] <= 9 || g_global.command[i] >= 13))
                     i++;
            }
    }
}

static void pre_parse_command(void)
{
    int i;

    i = 0;
    check_nb_command(void);
    g_global.flag_command = (int *[4])malloc((sizeof(int[4])) * g_global.nb_command)
    if (!g_global.flag_command)
        free_and_exit(MEMO)


    while (g_global.command[i])
    {
        C
    }
}

void    parse_command(void)
{
    pre_parse_command(void);
}





if (ft_strnstr(g_global.command, "exit", 6)) // a ajouter au parsinng 
		g_global.statut = EXIT_SUCCESS; // a ajouter au parsinng