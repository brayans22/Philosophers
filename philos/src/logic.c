/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:27:37 by brayan            #+#    #+#             */
/*   Updated: 2024/02/06 23:49:35 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosopher.h"

/*
 * Pre: -
 * Post: Wrapper rutina de comida
*/
static void	wrapper_eat(t_philo *philo)
{
	long	time_d;

	set_mutex_status(&philo->right_fork->fork_thread_mtx, LOCK_MTX);
	print_simulation(philo->program, philo, TAKE_A_FORK, get_time_ms() - \
			philo->program->time_start);
	set_mutex_status(&philo->left_fork->fork_thread_mtx, LOCK_MTX);
	print_simulation(philo->program, philo, TAKE_A_FORK, get_time_ms() - \
			philo->program->time_start);
	ft_usleep(1);
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
static void	routine(t_philo *philo)
{
	if (philo->program->limits_meals == EMPTY)
		wrapper_eat(philo);
	else if (philo->counter_meals + 1 < philo->program->limits_meals)
		wrapper_eat(philo);
	else
	{
		set_mutex_status(&philo->philo_mtx, LOCK_MTX);
		philo->is_full = TRUE;
		set_mutex_status(&philo->philo_mtx, UNLOCK_MTX);
		set_total_philos_full(philo->program);
		if (get_total_philos_full(philo->program) \
		>= philo->program->total_philos)
			set_is_end(philo->program);
	}
}

/*
 * Pre: -
 * Post: Realiza la rutina de un philosopher.
 *      
*/
static void	*philo_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	set_mutex_status(&philo->program->get_time_mutex, LOCK_MTX);
	philo->last_meal_time = get_time_ms() + philo->program->time_to_die;
	set_mutex_status(&philo->program->get_time_mutex, UNLOCK_MTX);
	while (!get_is_end(philo->program))
	{
		if (!philo->is_full)
			routine(philo);
		print_simulation(philo->program, philo, THINKING, get_time_ms() - \
		philo->program->time_start);
		print_simulation(philo->program, philo, SLEEPING, get_time_ms() - \
		philo->program->time_start);
		ft_usleep(philo->program->time_to_sleep);
		if (get_is_end(philo->program))
			break ;
		if (get_total_philos_full(philo->program) + 1 >= \
	 	philo->program->total_philos)
		{
			wrapper_eat(philo);
			set_is_end(philo->program);
			break ;
		}
	}
	return (NULL);
}

/*
 * Pre: -
 * Post: Inicia el programa (La cena de los philosophos).
*/
int	start_program(t_program *program)
{
	int	i;

	i = -1;
	program->time_start = get_time_ms();
	while (++i < program->total_philos && !get_is_end(program))
	{
		if (set_thread(&(program->philos[i].thread_id), CREATE_THREAD \
		, &philo_routine, &program->philos[i]) != OK)
			return (ERROR);
		ft_usleep(5);
	}
	set_thread(&program->thread_monitor, CREATE_THREAD \
	, &monitor, program);
	i = -1;
	while (++i < program->total_philos)
		set_thread(&program->philos[i].thread_id, JOIN_THREAD, NULL, NULL);
	set_thread(&program->thread_monitor, JOIN_THREAD, NULL, NULL);
	return (OK);
}
