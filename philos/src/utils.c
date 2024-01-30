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
long long get_time_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

/*
 * PRE: -
 * POST: Libera la memoria usada en el programa (threads, mutex, structs...)
 */
int ft_clean_program(t_program *program)
{
	int i;

	i = -1;
	while (++i < program->total_philos)
    {
        if (set_thread(&(program->philos[i].thread_id), JOIN_THREAD, NULL, NULL) != OK)
            return (ERROR);
    }
	i = -1;
	while (++i < program->total_philos)
		set_mutex_status(&program->forks[i].fork_thread_mtx, DESTROY_MTX);
	set_mutex_status(&program->end_mutex, DESTROY_MTX);
	set_mutex_status(&program->print_mutex, DESTROY_MTX);
	free(program->forks);
	free(program->philos);
	return (OK);
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
void print_simulation(t_program *program, t_philo *philo, int action)
{
	long time_passed;
	if (set_mutex_status(&program->print_mutex, LOCK_MTX) != OK)
        return ;
	time_passed = get_time_ms() - program->time_start;
	if (TAKE_A_FORK == action)
		printf("⏳ %-3ld ms | 👴🏻 %d | Action: has taken a fork 🥄\n", time_passed, philo->id);
	else if (EATING == action)
		printf("⏳ %-3ld ms | 👴🏻 %d | Action: is eating 🍲\n", time_passed, philo->id);
	else if (SLEEPING == action)
		printf("⏳ %-3ld ms | 👴🏻 %d | Action: is sleeping 🛌\n", time_passed, philo->id);
	else if (THINKING == action)
		printf("⏳ %-3ld ms | 👴🏻 %d | Action: is thinking 🧠\n", time_passed, philo->id);
	else if (DIED == action)
		printf("⏳ %-3ld ms | 👴🏻 %d | Action: is died 💀\n", time_passed, philo->id);
	printf("______________________________________________________________________________________________________\n");
	set_mutex_status(&program->print_mutex, UNLOCK_MTX);
}

/*
 * PRE: -
 * POST: Duerme el programa miliseconds
 */
int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time_ms();
	while ((((size_t)get_time_ms() - start) < milliseconds))
		usleep(500);
	return (0);
}