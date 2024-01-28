#include "../headers/philosopher.h"

static void *case_one_philo(void *data)
{
    t_program   *program;
    int         total_threads_running;         

    program = (t_program *)data;
    if (!program)
        return (NULL);
    if (set_mutex_status(&(program->philos[0].philo_mutex), LOCK_MTX) != OK)
        return(NULL);
        total_threads_running = 0;
        program->philos[0].last_meal_time = get_time_ms();
        total_threads_running++;
    if (program->philos[0].is_full) //SI ESTA LLENO TERMINO EL PROGRAMA.
        return (NULL);
    if (set_mutex_status(&(program->philos[0].philo_mutex), UNLOCK_MTX) != OK)
        return(NULL);
	print_case(TAKE_FIRST_FORK, program->philos[0], ACTIVATE_DETAILS);
	while (!program->is_end)
        ft_usleep(200);
		//precise_usleep(200, program);
	return (NULL);
}

int start_program(t_program *program)
{
    int i;

    i = -1;
    if (!program)
        return (ERROR);
    //Si el limite de comidas es 0, quiere decir que
    //no hay nada commer o ya "comieron" jajaja
    if (program->limits_meals == 0)
        return (OK);
    else if (program->total_philos == 1) // SOLO HAY UN PHILO, obviamente no hay race condition
    {
        if (set_thread(&(program->philos[0].thread_id), CREATE_THREAD, case_one_philo) != OK)
            return (ERROR);
    } 
    else
    {
        //creamos los threads para cada philo
        /*
        while (++i < program->total_philos)
            if (set_thread(&(program->philos[i].thread_id), CREATE_THREAD, dinner) != OK)
                return (ERROR);
        */
    }
    // IMPLEMENTAR MONITORING & crear el mutex
    if (set_thread(&(program->philos[0].philo_mutex), CREATE_THREAD, monitoring) != OK)
        return(NULL);
    if (set_mutex_status(&(program->program_mutex), LOCK_MTX) != OK)
        return(NULL);
    program->time_start = get_time_ms();
    program->all_threads_ready = TRUE;
    if (set_mutex_status(&(program->program_mutex), UNLOCK_MTX) != OK)
        return(NULL);
	i = -1;
	while (++i < program->total_philos)
    {
        if (set_thread(&(program->philos[i].thread_id), JOIN_THREAD, NULL) != OK)
            return(NULL);
    }
    if (set_mutex_status(&(program->program_mutex), LOCK_MTX) != OK)
        return(NULL);
    program->is_end = TRUE;
    if (set_mutex_status(&(program->monitor_mutex), UNLOCK_MTX) != OK)
        return(NULL);
    return (OK);
}

