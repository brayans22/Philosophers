/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsaiago- <bsaiago-@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:35:10 by bsaiago-          #+#    #+#             */
/*   Updated: 2024/01/18 20:50:27 by bsaiago-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosopher.h"

/*
 * PRE: -
 * POST: Devuelve el tiempo actual transcurrido en milisegundos.
 */
long get_time_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == ERROR)
		return (ft_putendl_fd("gettimeofday() error", 2), -1);
	return (((long)time.tv_sec * 1000) + (time.tv_usec / 1000));
}

/*
 * PRE: -
 * POST: Muestra un string s en la terminal seguido de un salto de linea '\n'
 */
void ft_putendl_fd(char *s, int fd)
{
	char *first;

	first = s;
	if (fd == ERROR)
		return;
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
 * POST: Mostrara por consola la action (Sleeping, Thinking, Eating) que corresponda con el philo
 */
void print_simulation(t_program *program, t_philo *philo, int action, long time_passed)
{
	set_mutex_status(&program->print_mutex, LOCK_MTX);
	//printf("PHILO ID: %i\n", philo->id);
	if (!get_is_end(program))
		printf("________________________________________________________________________________\n");
	if (TAKE_A_FORK == action && !get_is_end(program))
		printf("⏳ %ld ms | 👴🏻 %d | Action: has taken a fork 🥄\n", time_passed, philo->id);
	else if (EATING == action && !get_is_end(program))
		printf("⏳ %ld ms | 👴🏻 %d | Action: is eating 🍲\n", time_passed, philo->id);
	else if (SLEEPING == action && !get_is_end(program))
		printf("⏳ %ld ms | 👴🏻 %d | Action: is sleeping 🛌\n", time_passed, philo->id);
	else if (THINKING == action && !get_is_end(program))
		printf("⏳ %ld ms | 👴🏻 %d | Action: is thinking 🧠\n", time_passed, philo->id);
	else if (DEAD == action)
		printf("⏳ %ld ms | 👴🏻 %d | Action: is died 💀\n", time_passed, philo->id);
	if (!get_is_end(program))
		printf("________________________________________________________________________________\n");
	set_mutex_status(&program->print_mutex, UNLOCK_MTX);
}

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