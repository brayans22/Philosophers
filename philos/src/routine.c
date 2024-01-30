#include "../headers/philosopher.h"

static void check_stop_eat_philo(t_philo *philo)
{
    set_mutex_status(&philo->program->end_mutex, LOCK_MTX);
    print_simulation(philo->program, philo, EATING);
    ft_usleep(philo->program->time_to_eat);
    philo->last_meal_time = get_time_ms();
    if (++philo->counter_meals == philo->program->limits_meals)
    {
        philo->program->count_philos_full++;
        if (++philo->program->count_philos_full == philo->program->total_philos)
            philo->program->is_end = TRUE;
        else
            philo->last_meal_time = get_time_ms();
    }
    set_mutex_status(&philo->program->end_mutex, UNLOCK_MTX);
}

static void	eat_routine(t_philo *philo)
{
    if (set_mutex_status(&philo->right_fork->fork_thread_mtx, LOCK_MTX) != OK)
        return ;
    if (set_mutex_status(&philo->left_fork->fork_thread_mtx, LOCK_MTX) != OK)
        return ; 
    print_simulation(philo->program, philo, TAKE_A_FORK);
    print_simulation(philo->program, philo, TAKE_A_FORK);
    if (set_mutex_status(&philo->left_fork->fork_thread_mtx, UNLOCK_MTX) != OK)
        return ;
    if (set_mutex_status(&philo->right_fork->fork_thread_mtx, UNLOCK_MTX) != OK)
        return ; 
    check_stop_eat_philo(philo);
}

void *philo_routine(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;
    if (!philo)
        return (NULL);
    
    while (1)
    {
        set_mutex_status(&philo->program->end_mutex, LOCK_MTX);
		if (philo->program->is_end == 1)
		{
			pthread_mutex_unlock(&philo->program->end_mutex);
			break ;
		}
        set_mutex_status(&philo->program->end_mutex, UNLOCK_MTX);
        eat_routine(philo);
        print_simulation(philo->program, philo, SLEEPING);
        ft_usleep(philo->program->time_to_sleep);
        print_simulation(philo->program, philo, THINKING);
    }
    return (NULL);
}
