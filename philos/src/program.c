#include "../headers/philosopher.h"

/*
 * Pre: -
 * Post: Wrapper rutina de comida
*/
static void wrapper_eat(t_philo *philo)
{
    long time_last_meal;

    set_mutex_status(&philo->right_fork->fork_thread_mtx, LOCK_MTX);
    set_mutex_status(&philo->left_fork->fork_thread_mtx, LOCK_MTX);
    print_simulation(philo->program, philo, TAKE_A_FORK);
    print_simulation(philo->program, philo, TAKE_A_FORK);
    print_simulation(philo->program, philo, EATING);
    ft_usleep(philo->program->time_to_eat);
    philo->counter_meals++;
    set_mutex_status(&philo->program->get_time_mutex, LOCK_MTX);
    time_last_meal = get_time_ms() - philo->program->time_start;
    philo->last_meal_time = time_last_meal;
    set_mutex_status(&philo->program->get_time_mutex, UNLOCK_MTX);
    set_mutex_status(&philo->left_fork->fork_thread_mtx, UNLOCK_MTX);
    set_mutex_status(&philo->right_fork->fork_thread_mtx, UNLOCK_MTX);
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
        philo->is_full = TRUE;
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
void *philo_routine(void *data)
{
    t_philo *philo;
    long time_wait;

    philo = (t_philo *)data;
    time_wait = philo->program->time_to_die + philo->program->time_to_eat + philo->program->time_to_sleep;
    if (!philo)
        return (NULL);
    if (philo->id % 2)
		usleep(time_wait);
    while (!get_is_end(philo->program))
    {
        eat_routine(philo);
        if (get_is_end(philo->program))
            break ;
        else
        {
            usleep(time_wait);
            ft_usleep(philo->program->time_to_sleep);
            print_simulation(philo->program, philo, SLEEPING);
            print_simulation(philo->program, philo, THINKING);
        }
        
    }
    return (NULL);
}

/*
 * Pre: -
 * Post: Verifica si el programa se acabo, es decir, si
 *       Un philo se muere, o todos estan llenos.
*/
void	*monitor_program(void *data)
{
	int             i;
    long            last_meal_time;
    long            current_time;
	t_program		*program;

	program = (t_program *)data;
    
    while (!get_is_end(program))
	{
        i = -1;
        current_time = get_time_ms() - program->time_start;
        while (++i < program->total_philos)
		{
            set_mutex_status(&program->get_time_mutex, LOCK_MTX);
            last_meal_time = current_time - program->philos[i].last_meal_time;
            set_mutex_status(&program->get_time_mutex, UNLOCK_MTX);
			if (last_meal_time > program->time_to_die)
            {
                print_simulation(program, &program->philos[i], DEAD);
                set_is_end(program);
                return (NULL);
            }
		}
        ft_usleep(1);
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
        ft_usleep(20);
    }
    set_thread(&program->thread_monitor, CREATE_THREAD, monitor_program, program);
    i = -1;
    while (++i < program->total_philos)
    {
        set_thread(&program->philos[i].thread_id, JOIN_THREAD, NULL, NULL);
    }
    set_thread(&program->thread_monitor, JOIN_THREAD, NULL, NULL);
    return (OK);
}
