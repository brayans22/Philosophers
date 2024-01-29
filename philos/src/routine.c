#include "../headers/philosopher.h"

static void check_stop_eat_philo(t_philo *philo)
{
    if (++philo->counter_meals == philo->program->limits_meals)
    {
        if (++philo->program->count_philos_full == philo->program->total_philos)
        {
            philo->program->is_end = TRUE;
            if (set_mutex_status(&philo->program->mutex_is_end, LOCK_MTX) != OK)
                return ;
        }
    }
}

static void	eat_routine(t_philo *philo)
{
    while (TRUE)
    {
        //if (set_mutex_status(&philo->right_fork->fork_thread_mtx, LOCK_MTX) != OK)
        //   break ;
        //print_simulation(philo->program, philo, TAKE_A_FORK);
        //if (set_mutex_status(&philo->left_fork->fork_thread_mtx, LOCK_MTX) != OK)
        //    break ; 
        //print_simulation(philo->program, philo, TAKE_A_FORK);
        philo->last_meal_time = get_time_ms();
        //print_simulation(philo->program, philo, EATING);
        ft_usleep(philo->program->time_to_eat);
        check_stop_eat_philo(philo);
        //if (set_mutex_status(&philo->left_fork->fork_thread_mtx, UNLOCK_MTX) != OK)
        //    break ;
        //if (set_mutex_status(&philo->right_fork->fork_thread_mtx, UNLOCK_MTX) != OK)
        //    break ;  
    }
}

void *philo_routine(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;
    if (!philo)
        return (NULL);
    while (TRUE)
    {
        
        eat_routine(philo);
        print_simulation(philo->program, philo, SLEEPING);
        print_simulation(philo->program, philo, THINKING);
        ft_usleep(philo->program->time_to_sleep);
        
        //Ya que el subject no aclara cuanto es el tiempo para pensar
    }
    return (NULL);
}
