#include "../headers/philosopher.h"

static int aux_start_program (t_program *program)
{
    int i;

    if (set_mutex_status(&program->program_mutex, LOCK_MTX) != OK)
        return (ERROR);
    if (set_thread(&program->monitor_thread, CREATE_THREAD, monitor_program, program) != OK)
        return (ERROR);
    if (set_mutex_status(&program->program_mutex, UNLOCK_MTX) != OK)
        return (ERROR);
    i = -1;
	while (++i < program->total_philos)
    {
        if (set_mutex_status(&program->philos[i].philo_mutex, LOCK_MTX) != OK)
            return (ERROR);
        if (set_thread(&(program->philos[i].thread_id), JOIN_THREAD, NULL, NULL) != OK)
            return (ERROR);
        if (set_mutex_status(&program->philos[i].philo_mutex, UNLOCK_MTX) != OK)
            return (ERROR);
    }
    if (set_mutex_status(&program->program_mutex, UNLOCK_MTX) != OK)
        return (ERROR);
    return (OK);
}

int start_program(t_program *program)
{
    int i;

    i = -1;
    if (set_mutex_status(&program->program_mutex, LOCK_MTX) != OK)
        return (ERROR);
    if (program->limits_meals == 0)
        return (OK);
    else
    {
        program->time_start = get_time_ms();
        while (++i < program->total_philos)
        {
            if (set_mutex_status(&program->philos[i].philo_mutex, LOCK_MTX) != OK)
                return (ERROR);
            if (set_thread(&(program->philos[i].thread_id), CREATE_THREAD, philo_routine, &program->philos[i]) != OK)
                return (ERROR);
            ft_usleep(100);
            if (set_mutex_status(&program->philos[i].philo_mutex, UNLOCK_MTX) != OK)
                return (ERROR);
        }
    }
    if (set_mutex_status(&program->program_mutex, UNLOCK_MTX) != OK)
        return (ERROR);
    aux_start_program(program);
    return (OK);
}
