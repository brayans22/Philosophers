#include "../headers/philosopher.h"

static ()
{
    
}

static void *case_one_philo(void *data)
{
    t_program   *program;
    int         total_threads_running;         

    program = (t_program *)data;
    if (!program)
        return (NULL);
    if (set_mutex_status(&(philos[0].philo_mutex), LOCK_MTX) != OK)
        return(NULL);
        total_threads_running = 0;
        program->last_meal_time = gettime(MILISECONDS);
        total_threads_running++;
        if (program->philos[0]->is_full) //SI ESTA LLENO TERMINO EL PROGRAMA.
            return (NULL);
    if (set_mutex_status(&(philos[0].philo_mutex), UNLOCK_MTX) != OK)
        return(NULL);
    
	if (set_mutex_status(&(philos[0].philo_mutex), LOCK_MTX) != OK)
        return(NULL);
    if (set_mutex_status(&(philos[0].philo_mutex), UNLOCK_MTX) != OK)
        return(NULL);
	write_status(TAKE_FIRST_FORK, philo, DEBUG_MODE);
	while (!simulation_finished(philo->table))
		precise_usleep(200, philo->table);
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
        if (set_thread(&(program->philos[i].thread_id), CREATE_THREAD, case_one_philo) != OK)
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

}