#include "../headers/philosopher.h"

int start_program(t_program *program)
{
    int i;

    i = -1;
    if (!program)
        return (ERROR);
    if (program->limits_meals == 0)
        return (OK);
    else
    {
        while (++i < program->total_philos)
        {
            if (set_thread(&(program->philos[i].thread_id), CREATE_THREAD, philo_routine, &program->philos[i]) != OK)
                return (ERROR);
            ft_usleep(200);
        }
    }
    monitor_program(program);
    return (OK);
}