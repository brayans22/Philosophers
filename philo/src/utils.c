/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:35:10 by bsaiago-          #+#    #+#             */
/*   Updated: 2024/02/09 14:29:36 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosopher.h"

/*
 * PRE: -
 * POST: Devuelve el tiempo actual transcurrido en milisegundos.
 */
long	get_time_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == ERROR)
		return (ft_putendl_fd("gettimeofday() error", 2), ERROR);
	return (((long)time.tv_sec * 1000) + (time.tv_usec / 1000));
}

/*
 * PRE: -
 * POST: Muestra un string s en la terminal seguido de un salto de linea '\n'
 */
void	ft_putendl_fd(char *s, int fd)
{
	char	*first;

	first = s;
	if (fd == ERROR)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
	write(fd, "\n", 1);
	s = first;
}

/*
 * PRE: -
 * POST: Mostrara por consola la action (Sleeping, Thinking, Eating) 
 * 		 que corresponda con el philo
 */
void	print_simulation(t_program *program, t_philo *philo \
, int action, long t)
{
	set_mutex_status(&program->print_mutex, LOCK_MTX);
	if (SLEEPING == action && !get_is_end(program))
		printf("%ld ms %d is sleeping\n", t, philo->id);
	else if (THINKING == action && !get_is_end(program))
		printf("%ld ms %d is thinking\n", t, philo->id);
	else if (TAKE_A_FORK == action && !get_is_end(program))
		printf("%ld ms %d has taken a fork\n", t, philo->id);
	else if (EATING == action && !get_is_end(program))
		printf("%ld ms %d is eating\n", t, philo->id);
	else if (DEAD == action)
		printf("%ld ms %d is died\n", t, philo->id);
	set_mutex_status(&program->print_mutex, UNLOCK_MTX);
}
/*
void	print_simulation(t_program *program, t_philo *philo \
, int action, long t)
{
	set_mutex_status(&program->print_mutex, LOCK_MTX);
	if (SLEEPING == action && !get_is_end(program))
		printf("⏳ %ld ms | 👴🏻 %d | is sleeping 🛌\n", t, philo->id);
	else if (THINKING == action && !get_is_end(program))
		printf("⏳ %ld ms | 👴🏻 %d | is thinking 🧠\n", t, philo->id);
	else if (TAKE_A_FORK == action && !get_is_end(program))
		printf("⏳ %ld ms | 👴🏻 %d | has taken a fork 🥄\n", t, philo->id);
	else if (EATING == action && !get_is_end(program))
		printf("⏳ %ld ms | 👴🏻 %d | is eating 🍲\n", t, philo->id);
	else if (DEAD == action)
		printf("⏳ %ld ms | 👴🏻 %d | is died 💀\n", t, philo->id);
	if (!get_is_end(program))
		printf("_______________________________________________________\n");
	set_mutex_status(&program->print_mutex, UNLOCK_MTX);
}
*/

/*
 * PRE: -
 * POST: Duerme el program time_in_ms
 */
void	ft_usleep(long long time)
{
	time += get_time_ms();
	while (get_time_ms() <= time)
		usleep(200);
}
