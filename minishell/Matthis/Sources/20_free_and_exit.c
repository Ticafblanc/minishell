/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_free_and_exit.c                                  :+:      :+:    :+:   */
/*   By: sbouras <sbouras@student.42quebec.com>       +:+ +:+         +:+     */
/*   By: mdoquocb <mdoquocb@student.42quebec.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 18:29:46 by mdoquocb          #+#    #+#             */
/*   Updated: 2022/06/11 18:30:06 by mdoquocb         ###   ########.ca       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int free_and_exit(int statut, t_global *global)
{
    if (statut == EXIT_SUCCESS)
    {
        global->statut == EXIT_SUCCESS;
    }
    return (EXIT_SUCCESS);
}

