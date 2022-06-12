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

void    start(t_global *global)
{
    t_philo         **philo;
    int id;

    philo = global->philo;
    id = 0;
    global->statut = ALIVE;
    while (id < global->number_of_philosophers)
    {
        pthread_create(&(philo[id]->thread_id), NULL, loop_philo, philo[id]);
        pthread_detach(global->philo[id]->thread_id);
        id++;
    }
    return ;
}


