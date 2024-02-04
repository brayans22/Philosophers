/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsaiago- <bsaiago-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 21:18:00 by bsaiago-          #+#    #+#             */
/*   Updated: 2024/02/04 20:31:59 by bsaiago-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosopher.h"

static int	assign_fork_to_philo(t_philo *philo, t_fork *forks, \
		int index_philo, int total_philos)
{
	if (!philo || !forks)
		return (ERROR);
	philo->left_fork = &forks[0];
	philo->right_fork = &forks[0];
	if (total_philos > 1)
	{
		if (philo->id % 2 == 1)
		{
			philo->right_fork = &forks[index_philo];
			philo->left_fork = &forks[(index_philo + 1) % total_philos];
		}
		else
		{
			philo->right_fork = &forks[(index_philo + 1) % total_philos];
			philo->left_fork = &forks[index_philo];
		}
	}
	return (OK);
}

static int	init_philos(t_philo **philos, long total_philos \
		, t_fork *forks, t_program *program)
{
	int	i;

	i = -1;
	(*philos) = get_malloc_memory(sizeof(t_philo) * total_philos);
	if (!(*philos) && !philos)
		return (ERROR);
	if (!forks)
		return (free(*philos), ERROR);
	while (++i < total_philos)
	{
		(*philos)[i].id = i + 1;
		(*philos)[i].counter_meals = 0;
		(*philos)[i].last_meal_time = NOT_EAT_YET;
		(*philos)[i].time_to_die = program->time_to_die;
		if (assign_fork_to_philo(&((*philos)[i]), forks, i, total_philos) != OK)
			return (ERROR);
		(*philos)[i].program = program;
		(*philos)[i].is_full = FALSE;
	}
	return (OK);
}

static int	init_forks(t_fork **forks, long total_philos)
{
	int	i;

	i = -1;
	*forks = get_malloc_memory(sizeof(t_fork) * total_philos);
	if (!(*forks) && !forks)
		return (ERROR);
	while (++i < total_philos)
	{
		if (pthread_mutex_init(&((*forks)[i].fork_thread_mtx), NULL) != 0)
			return (ERROR);
		(*forks)[i].id = i;
	}
	return (OK);
}

static int	wrapper_init_program(t_program *program)
{
	if (!program)
		return (ERROR);
	program->is_end = FALSE;
	program->count_philos_full = 0;
	pthread_mutex_init(&program->print_mtx, NULL);
	pthread_mutex_init(&program->count_philos_full_mtx, NULL);
	pthread_mutex_init(&program->count_philos_full_mtx, NULL);
	pthread_mutex_init(&program->end_mtx, NULL);
	if (init_forks(&program->forks, program->total_philos) != OK)
		return (ft_putendl_fd(MESSAGE_ERROR_MUTEX, 2), ERROR);
	if (init_philos(&program->philos, program->total_philos, program->forks, \
				program) != OK)
		return (ERROR);
	return (OK);
}

int	init_program(t_program *program)
{
	return (wrapper_init_program(program));
}
