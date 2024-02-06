#include "../headers/philosopher.h"

/*
 * Pre: -
 * Post: Wrapper rutina de comida
*/
static void wrapper_eat(t_philo *philo)
{
    long time_d;

    set_mutex_status(&philo->right_fork->fork_thread_mtx, LOCK_MTX);
    set_mutex_status(&philo->left_fork->fork_thread_mtx, LOCK_MTX);
    print_simulation(philo->program, philo, TAKE_A_FORK, get_time_ms() - \
            philo->program->time_start);
    print_simulation(philo->program, philo, TAKE_A_FORK, get_time_ms() - \
            philo->program->time_start);
    print_simulation(philo->program, philo, EATING, get_time_ms() - \
            philo->program->time_start);
    set_mutex_status(&philo->philo_mtx, LOCK_MTX);
    philo->is_eating = TRUE;
    set_mutex_status(&philo->philo_mtx, UNLOCK_MTX);
    if (!philo->is_full)
        philo->counter_meals++;
    ft_usleep(philo->program->time_to_eat);
    set_mutex_status(&philo->philo_mtx, LOCK_MTX);
    time_d = philo->program->time_to_die + get_time_ms();
    philo->last_meal_time = time_d;
    set_mutex_status(&philo->philo_mtx, UNLOCK_MTX);
    set_mutex_status(&philo->left_fork->fork_thread_mtx, UNLOCK_MTX);
    set_mutex_status(&philo->right_fork->fork_thread_mtx, UNLOCK_MTX);
    set_mutex_status(&philo->philo_mtx, LOCK_MTX);
    philo->is_eating = FALSE;
    set_mutex_status(&philo->philo_mtx, UNLOCK_MTX);
}

/*
 * Pre: -
 * Post: Ejecuta la rutina de comida de un philo.
*/
static void eat_routine(t_philo *philo)
{
    if(philo->program->limits_meals == EMPTY)
        wrapper_eat(philo);
    else if(philo->counter_meals + 1 <= philo->program->limits_meals)
        wrapper_eat(philo); 
    else if (!philo->is_full)
    {
        set_mutex_status(&philo->philo_mtx, LOCK_MTX);
        philo->is_full = TRUE;
        set_mutex_status(&philo->philo_mtx, UNLOCK_MTX);
        set_total_philos_full(philo->program);
        if (get_total_philos_full(philo->program) >= philo->program->total_philos)
            set_is_end(philo->program);
    }
}

/*
 * Pre: -
 * Post: Realiza la rutina de un philosopher.
 *      
*/
static void *philo_routine(void *data)
{
    t_philo *philo;

    philo = (t_philo *)data;
    if (!philo)
        return (NULL);
    set_mutex_status(&philo->program->get_time_mutex, LOCK_MTX);
    philo->last_meal_time = get_time_ms() + philo->program->time_to_die;
    set_mutex_status(&philo->program->get_time_mutex, UNLOCK_MTX);
    while (!get_is_end(philo->program))
    {
        if (!philo->is_full)
            eat_routine(philo);
        if (get_is_end(philo->program))
            break ;
        if (get_total_philos_full(philo->program) >= philo->program->total_philos)
            break ;
        if (!philo->is_full)
	    {
		    print_simulation(philo->program, philo, THINKING, get_time_ms() - \
            philo->program->time_start);
		    ft_usleep(philo->program->time_to_sleep);
            print_simulation(philo->program, philo, THINKING, get_time_ms() - \
            philo->program->time_start);
	    }
    }
    return (NULL);
}

/*
 * Pre: -
 * Post: Verifica si el programa se acabo.
*/
static void	*monitor_program(void *data)
{
    int             i;
    int             is_full;
    int             is_eating;
    long            last_meal_time;
	t_program		*program;

	program = (t_program *)data;
    i = 0;
    while (!get_is_end(program) && get_total_philos_full(program) < program->total_philos)
    {
        set_mutex_status(&program->philos[i].philo_mtx, LOCK_MTX);
        is_eating = program->philos[i].is_eating;
        is_full = program->philos[i].is_full;
        last_meal_time = program->philos[i].last_meal_time;
        set_mutex_status(&program->philos[i].philo_mtx, UNLOCK_MTX);
        if (get_time_ms() >= last_meal_time
        && !is_eating && !is_full)
        {
            print_simulation(program, &program->philos[i], DEAD, get_time_ms() - program->time_start);
            set_is_end(program);
        }
        i++;
        if (i == program->total_philos)
            i = 0;
	}
    return (NULL);
}

/*
 * Pre: -
 * Post: Inicia el programa (La cena de los philosophos).
*/
int start_program(t_program *program)
{
    int i;

    i = -1;
    program->time_start = get_time_ms();
    while (++i < program->total_philos)
    {
        if (set_thread(&(program->philos[i].thread_id), CREATE_THREAD \
            ,philo_routine, &program->philos[i]) != OK)
            return (ERROR);
        ft_usleep(2);
    }
    set_thread(&program->thread_monitor, CREATE_THREAD, monitor_program, program);
    i = -1;
    while (++i < program->total_philos)
        set_thread(&program->philos[i].thread_id, JOIN_THREAD, NULL, NULL);
    set_thread(&program->thread_monitor, JOIN_THREAD, NULL, NULL);
    return (OK);
}
