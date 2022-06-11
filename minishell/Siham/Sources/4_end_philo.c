#include <philo.h>

void    sleep_check(t_global *global, int statut)
{
    int   end_time;

    if (statut == EAT)
    {
        end_time = global->timestamp + global->time_to_eat;
        while (global->statut == ALIVE 
                && end_time > global->timestamp)
            usleep(100);
    }
    else if (statut == SLEEP)
    {
        end_time = global->time_to_sleep + global->timestamp;
        while (global->statut == ALIVE 
                && end_time > global->timestamp)
            usleep(100);
    }
}

void    loop_healt(t_global *global)
{
    t_philo         **philo;
    int id;

    philo = global->philo;
    usleep(1000 * global->number_of_philosophers);
    while (global->statut == ALIVE)
    {
        id = -1;
        while (++id < global->number_of_philosophers
                && global->statut == ALIVE)
        {
            if ((philo[id]->last_meal_timestamp + global->time_to_die)
                < global->timestamp)
                {
                    global->statut = DEAD;
                }
               
            if (global->number_of_times_each_philosopher_must_eat == 0)
                global->statut = DONE;
        }       
    }
    put_success(global->philo[--id], global->statut);
    return ;
}

int wait_philo(t_global *global)
{
    int         id;
    t_philo     **philo;

    id = 0;
    philo = global->philo;
    while (id < global->number_of_philosophers)
    {
        pthread_mutex_destroy(&(philo[id]->fork));
        id++;
    }
    pthread_mutex_destroy(&global->print);
    return (7);
}
