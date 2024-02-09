/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:32:08 by brayan            #+#    #+#             */
/*   Updated: 2024/02/09 15:47:08 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosopher.h"

/*
 * Pre: -
 * Post: Wrapper monitor.
*/
static void	*wrapper_monitor(t_program *program \
, long last_meal_time)
{
	int	i;

	i = 0;
	while (!get_is_end(program) && get_total_philos_full(program) \
	< program->total_philos)
	{
		set_mutex_status(&program->philos[i].philo_mtx, LOCK_MTX);
		last_meal_time = program->philos[i].last_meal_time;
		set_mutex_status(&program->philos[i].philo_mtx, UNLOCK_MTX);
		if (get_time_ms() > last_meal_time)
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
	long			last_meal_time;
	t_program		*program;

	program = (t_program *)data;
	last_meal_time = 0;
	return (wrapper_monitor(program, last_meal_time));
}
