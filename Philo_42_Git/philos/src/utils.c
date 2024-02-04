/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsaiago- <bsaiago-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 19:35:10 by bsaiago-          #+#    #+#             */
/*   Updated: 2024/02/04 22:26:09 by bsaiago-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosopher.h"

long	get_time_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (ft_putendl_fd("gettimeofday() error", 2), -1);
	return ((time.tv_sec * (long)1000) + (time.tv_usec / 1000));
}

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

void	ft_usleep(long long time)
{
	time += get_time_ms();
	while (get_time_ms() <= time)
		usleep(200);
}

void	print_simulation(t_program *program, t_philo *p, int action)
{
	long	t;

	t = get_time_ms() - program->time_start;
	pthread_mutex_lock(&program->print_mtx);
	if (!get_bool(program->end_mtx, program->is_end))
		printf("________________________________________________________\n");
	if (TAKE_A_FORK == action && !get_bool(program->end_mtx, program->is_end))
		printf("⏳ %-3ld ms | 👴🏻 %d | has taken a fork 🥄\n", t, p->id);
	else if (EATING == action && !get_bool(program->end_mtx, program->is_end))
		printf("⏳ %-3ld ms | 👴🏻 %d | is eating 🍲\n", t, p->id);
	else if (SLEEPING == action && !get_bool(program->end_mtx, program->is_end))
		printf("⏳ %-3ld ms | 👴🏻 %d | is sleeping 🛌\n", t, p->id);
	else if (THINKING == action && !get_bool(program->end_mtx, program->is_end))
		printf("⏳ %-3ld ms | 👴🏻 %d | is thinking 🧠\n", t, p->id);
	else if (DEAD == action)
		printf("⏳ %-3ld ms | 👴🏻 %d | is died 💀\n", t, p->id);
	if (!get_bool(program->end_mtx, program->is_end))
		printf("________________________________________________________\n");
	pthread_mutex_unlock(&program->print_mtx);
}

int	free_program(t_program *program)
{
	int	i;

	i = -1;
	while (++i < program->total_philos)
		pthread_mutex_destroy(&program->forks[i].fork_thread_mtx);
	pthread_mutex_destroy(&program->end_mtx);
	pthread_mutex_destroy(&program->print_mtx);
	pthread_mutex_destroy(&program->count_philos_full_mtx);
	pthread_mutex_destroy(&program->program_mtx);
	if (program->forks)
		free(program->forks);
	if (program->philos)
		free(program->philos);
	free(program);
	return (OK);
}