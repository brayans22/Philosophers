#include "../headers/philosopher.h"

/*
 * Pre: -
 * Post: Ejectura la rutina de comida de un philo.
*/
static void	eat_routine(t_philo *philo)
{
    set_mutex_status(&philo->program->routine_mutex, LOCK_MTX);
    set_mutex_status(&philo->right_fork->fork_thread_mtx, LOCK_MTX);
    print_simulation(philo->program, philo, TAKE_A_FORK);
    set_mutex_status(&philo->right_fork->fork_thread_mtx, UNLOCK_MTX);

    set_mutex_status(&philo->left_fork->fork_thread_mtx, LOCK_MTX);
    print_simulation(philo->program, philo, TAKE_A_FORK);
    set_mutex_status(&philo->left_fork->fork_thread_mtx, UNLOCK_MTX);
    
    print_simulation(philo->program, philo, EATING);

    
    set_mutex_status(&philo->data_philo, LOCK_MTX);
    usleep(philo->program->time_to_eat);
    philo->counter_meals++;
    philo->last_meal_time = get_time_ms();
    set_mutex_status(&philo->data_philo, UNLOCK_MTX);
    set_mutex_status(&philo->program->routine_mutex, UNLOCK_MTX);
}

/*
 * Pre: -
 * Post: Realiza la rutina de un philosopher.
 *      
*/
void *philo_routine(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;
    if (!philo)
        return (NULL);
    while (!get_is_end(philo->program))
    {
        if ((philo->program->limits_meals == EMPTY)
            || (philo->counter_meals < philo->program->limits_meals))
            eat_routine(philo);
        print_simulation(philo->program, philo, SLEEPING);
        usleep(philo->program->time_to_sleep);
        print_simulation(philo->program, philo, THINKING);
    }
    return (NULL);
}
