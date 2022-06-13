/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_start.c                                          :+:      :+:    :+:   */
/*   By: sbouras <sbouras@student.42quebec.com>       +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/06/13 14:57:42 by jrossign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int    start_minishell(t_global *global)
{
    while (global->statut == ON)
    {
        global->command = readline("Minishell % ");
        if (global->command && *global->command)
            add_history(global->command);
        //if (strnstr(global->command, "clear", 6))//a ajouter a parsing
            //rl_clear_history(); 
        ft_putstr(global->command); //test a suprimer
        write (1, "\n", 1); // test a supprimer
        if (strnstr(global->command, "exit", 6))//a ajouter a parsing
            global->statut = OFF;// a ajouter au parsing
    }
    return (0) ;
}


