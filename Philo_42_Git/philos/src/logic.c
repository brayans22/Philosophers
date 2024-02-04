/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsaiago- <bsaiago-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 00:30:14 by bsaiago-          #+#    #+#             */
/*   Updated: 2024/02/04 22:57:44 by bsaiago-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosopher.h"

static void	sleep_routine(t_philo *philo)
{
	if (!philo->is_full)
	{
		print_simulation(philo->program, philo, SLEEPING);
		ft_usleep(philo->program->time_to_sleep);
	}
}

static void	eat_and_sleep_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_fork->fork_thread_mtx);
	print_simulation(philo->program, philo, TAKE_A_FORK);
	pthread_mutex_lock(&philo->left_fork->fork_thread_mtx);
	print_simulation(philo->program, philo, TAKE_A_FORK);
	print_simulation(philo->program, philo, EATING);
	ft_usleep(philo->program->time_to_eat);
	philo->counter_meals++;
	set_long(philo->program->program_mtx, &philo->time_to_die \
		, get_time_ms() + philo->program->time_to_die);
	if (philo->counter_meals == philo->program->limits_meals \
	&& philo->program->limits_meals != EMPTY)
	{
		philo->is_full = TRUE;
		set_int(philo->program->count_philos_full_mtx \
		, &philo->program->count_philos_full, 1);
		if (get_long(philo->program->count_philos_full_mtx \
		, philo->program->count_philos_full))
			set_bool(philo->program->end_mtx, &philo->program->is_end);
	}
	ft_usleep(philo->program->time_to_eat);
	pthread_mutex_unlock(&philo->right_fork->fork_thread_mtx);
	pthread_mutex_unlock(&philo->left_fork->fork_thread_mtx);
	sleep_routine(philo);
}

void	*routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	pthread_mutex_lock(&philo->program->program_mtx);
	philo->time_to_die = get_time_ms() + philo->program->time_to_die;
	pthread_mutex_unlock(&philo->program->program_mtx);
	if (philo->id % 2 == 0)
		ft_usleep(philo->program->time_to_eat / 10);
	while (1)
	{
		pthread_mutex_lock(&philo->program->program_mtx);
		if (!get_bool(philo->program->end_mtx, philo->program->is_end))
		{
			pthread_mutex_unlock(&philo->program->program_mtx);
			break ;
		}
		pthread_mutex_unlock(&philo->program->program_mtx);
		eat_and_sleep_routine(philo);
		if (philo->counter_meals == philo->program->total_philos)
			break ;
		print_simulation(philo->program, philo, THINKING);
	}
	return (NULL);
}

void	*monitor_program(void *data)
{
	t_program	*program;
	int			i;

	program = (t_program *)data;
	i = 0;
	while (!get_bool(program->end_mtx, program->is_end) \
	&& get_int(program->count_philos_full_mtx, program->count_philos_full) \
	< program->total_philos)
	{
		if (get_long(program->program_mtx, program->time_to_die) \
		<= get_time_ms() && get_bool(program->end_mtx, program->is_end))
		{
			set_bool(program->end_mtx, &program->is_end);
			print_simulation(program, &program->philos[i], DEAD);
		}
	}
	return (NULL);
}

int	start_program(t_program *program)
{
	int	i;

	i = -1;
	program->time_start = get_time_ms();
	while (++i < program->total_philos)
	{
		pthread_create(&program->philos[i].thread_id, NULL, \
		routine, &program->philos[i]);
		ft_usleep(5);
	}
	pthread_create(&program->monitor_thread, NULL, \
		monitor_program, &program);
	i = -1;
	while (++i < program->total_philos)
		pthread_join(program->philos[i].thread_id, NULL);
	pthread_join(program->monitor_thread, NULL);
	return (OK);
}
