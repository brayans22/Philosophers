/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:32:08 by brayan            #+#    #+#             */
/*   Updated: 2024/02/06 23:23:21 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosopher.h"

static void	*wrapper_monitor(t_program *program, int is_eating \
, long last_meal_time, int is_full)
{
	int	i;

	i = 0;
	while (!get_is_end(program) && get_total_philos_full(program) \
	< program->total_philos)
	{
		set_mutex_status(&program->philos[i].philo_mtx, LOCK_MTX);
		is_eating = program->philos[i].is_eating;
		is_full = program->philos[i].is_full;
		last_meal_time = program->philos[i].last_meal_time;
		set_mutex_status(&program->philos[i].philo_mtx, UNLOCK_MTX);
		if (get_time_ms() >= last_meal_time \
		&& !is_eating && !is_full)
		{
			print_simulation(program, &program->philos[i], \
			DEAD, get_time_ms() - program->time_start);
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
 * Post: Verifica si el programa se acabo.
*/
void	*monitor(void *data)
{
	int				is_full;
	int				is_eating;
	long			last_meal_time;
	t_program		*program;

	program = (t_program *)data;
	is_full = FALSE;
	is_eating = FALSE;
	last_meal_time = 0;
	return (wrapper_monitor(program, is_eating, last_meal_time, is_full));
}
