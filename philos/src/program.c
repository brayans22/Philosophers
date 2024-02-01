#include "../headers/philosopher.h"

/*
 * Pre: -
 * Post: Inicia el programa (La cena de los philosophos).
*/
int start_program(t_program *program)
{
    int i;

    i = -1;
    program->time_start = get_time_ms();
    if (program->limits_meals == 0)
        return (OK);
    else
    {
        while (++i < program->total_philos)
        {
            if (set_thread(&(program->philos[i].thread_id), CREATE_THREAD, philo_routine, &program->philos[i]) != OK)
                return (ERROR);
            usleep(50);
        }
    }
    monitor_program(program);
    return (OK);
}
