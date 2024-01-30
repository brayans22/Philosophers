#include "../headers/philosopher.h"

/*
 * Pre: -
 * Post: Verifica si el philo esta muerto o no, devolviendo el estado
 *       El philo esta muerto si su ultima comida pasa el time to died
 *       En otros caso sera, false.
 *       1e3 = 1000
*/
static int	is_philo_died(t_philo *philo, long time_to_die_philo)
{
    long            time_passed_without_meal;
    long            time_to_die_miliseconds; 
    int             died;

    died = FALSE;
    if (philo->counter_meals == philo->program->limits_meals)
        return (died);
    time_passed_without_meal = (get_time_ms() - philo->last_meal_time);
    time_to_die_miliseconds = time_to_die_philo;
    if (time_passed_without_meal > time_to_die_miliseconds)
        died = TRUE;
    if (set_mutex_status(&philo->philo_mutex, UNLOCK_MTX) != OK)
        return (FALSE);
    return (died);
}

/*
 * Pre: -
 * Post: Verifica si se acabo el programa se acabo, es decir, si
 *       Un philo se muere, 
*/
void	*monitor_program(void *data)
{
	int             i;
	t_program		*program;

	program = (t_program *)data;
    if (set_mutex_status(&program->program_mutex, LOCK_MTX) != OK)
        return (NULL);
    while (!program->is_end)
	{	
		i = -1;
        ft_usleep(2500);
		while (!program->is_end && ++i < program->total_philos)
		{
            if (set_mutex_status(&program->philos[i].philo_mutex, LOCK_MTX) != OK)
                return (NULL);
			if (is_philo_died(&program->philos[i], program->time_to_die))
			{
                program->is_end = TRUE;
				print_simulation(program, &program->philos[i], DIED);
			}
            if (set_mutex_status(&program->philos[i].philo_mutex, UNLOCK_MTX) != OK)
                return (NULL);
		}
	}
    return (set_mutex_status(&program->program_mutex, UNLOCK_MTX), NULL);
}