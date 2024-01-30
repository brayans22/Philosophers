#include "../headers/philosopher.h"

/*
 * Pre: -
 * Post: Verifica si el programa se acabo, es decir, si
 *       Un philo se muere, o todos estan llenos.
*/
void	*monitor_program(void *data)
{
	int             i;
    int             end;
    long            time_passed_without_meal;
    long            time_to_die_miliseconds; 
	t_program		*program;

	program = (t_program *)data;
    end = FALSE;
    
    set_mutex_status(&program->end_mutex, LOCK_MTX);
    while (!end && program->count_philos_full < program->total_philos)
	{
        printf("END: %i\n", end);
		i = -1;
        ft_usleep(2500);
        
		while (!program->is_end && ++i < program->total_philos && !end)
		{
			if (program->philos[i].counter_meals == program->limits_meals)
            {
                
                time_passed_without_meal = (get_time_ms() - program->philos[i].last_meal_time);
                time_to_die_miliseconds = program->time_to_die;
                if (time_passed_without_meal >= time_to_die_miliseconds)
                {
                    printf("ENTRE: %i\n", end);
                    end = TRUE;
                    print_simulation(program, &program->philos[i], DIED);
                    program->is_end = TRUE;
                }
            }
		}
        //end = 1;
        printf("END: %i\n", end);
	}
    set_mutex_status(&program->end_mutex, UNLOCK_MTX);
    return (NULL);
}