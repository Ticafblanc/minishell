/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_execute.c                                        :+:      :+:    :+:   */
/*   By: sbouras <sbouras@student.42quebec.com>       +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/06/13 15:10:10 by jrossign         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

extern t_global	g_global;

static void	find_command(void)
{
    int i;

    i = 0;
	while (*g_global.command
            && check_invisible_characters(*g_global.command))
            *g_global.command++;
    while (g_global.command[i] && g_global.command[i] != '|'
            || (g_global.command[i] != '&' && g_global.command [i + 1] != '&')
            || g_global.command[i] != '(')
            i++;
    g_global.

}

void    execute_command(char *command)
{
    while (*g_global.command)
    {
        find_command();
        child_process();
    }
}
