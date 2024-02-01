#include "../headers/philosopher.h"

/*
 * Pre: -
 * Post: Verifica si el programa se acabo, es decir, si
 *       Un philo se muere, o todos estan llenos.
*/
void	*monitor_program(void *data)
{
	int             i;
    long            time_passed_without_meal;
    long            time_to_die_miliseconds; 
	t_program		*program;

	program = (t_program *)data;
    while (!get_is_end(program) && get_total_philos_full(program) < program->total_philos)
	{
		i = -1;
		while (!get_is_end(program) && ++i < program->total_philos)
		{
            set_mutex_status(&program->philos[i].data_philo, LOCK_MTX);
			if (program->philos[i].counter_meals >= program->limits_meals \
                && program->limits_meals != EMPTY)
            {
                set_is_end(program);
                print_simulation(program, &program->philos[i], FULL);
            }
            else
            {
                time_passed_without_meal = (get_time_ms() - program->philos[i].last_meal_time);
                time_to_die_miliseconds = program->time_to_die;
                if (time_passed_without_meal >= time_to_die_miliseconds)
                {
                    print_simulation(program, &program->philos[i], DIED);
                    set_is_end(program);
                }
            }
            set_mutex_status(&program->philos[i].data_philo, UNLOCK_MTX);
		}
	}
    return (NULL);
}