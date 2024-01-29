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
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

/*
 * PRE: -
 * POST: Libera la memoria usada en el programa (threads, mutex, structs...)
 */
int ft_clean_program(t_program *program)
{
	t_philo *philo;
	int i;

	i = -1;
	while (++i < program->total_philos)
	{
		philo = &program->philos[i];
		if (set_mutex_status(&philo->philo_mutex, DESTROY_MTX) != OK)
			return (ERROR);
	}
	if (set_mutex_status(&program->print_mutex, DESTROY_MTX) != OK)
		return (ERROR);
	if (set_mutex_status(&program->program_mutex, DESTROY_MTX) != OK)
		return (ERROR);
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
 * POST: -
 */
static void select_case_to_print(t_program *program, t_philo *philo, int action, long time_passed)
{
	if (set_mutex_status(&program->program_mutex, LOCK_MTX) != OK)
	{
		set_mutex_status(&program->program_mutex, UNLOCK_MTX);
		return ;
	}
	if ((TAKE_FIRST_FORK == action || TAKE_A_FORK) && !program->is_end)
		printf("%-6ld %d has taken a fork\n", time_passed, philo->id);
	else if (EATING == action && !program->is_end)
		printf("%-6ld %d is eating\n", time_passed, philo->id);
	else if (SLEEPING == action && !program->is_end)
		printf("%-6ld %d is sleeping\n", time_passed, philo->id);
	else if (THINKING == action && !program->is_end)
		printf("%-6ld %d is thinking\n", time_passed, philo->id);
	else if (DIED == action)
		printf("%-6ld %d is died\n", time_passed, philo->id);
	set_mutex_status(&program->program_mutex, UNLOCK_MTX);
}

/*
 * PRE: -
 * POST: Mostrara por consola la routine (Sleeping, Thinking, Eating) que corresponda con el philo
 */
void print_simulation(t_program *program, t_philo *philo, int routine)
{
	long time_passed;

	if (set_mutex_status(&program->program_mutex, LOCK_MTX) != OK)
	{
		set_mutex_status(&program->program_mutex, UNLOCK_MTX);
		return ;
	}
	time_passed = get_time_ms() - program->time_start;
	printf("TIME PASSED: %li\n", time_passed);
	if (set_mutex_status(&program->program_mutex, UNLOCK_MTX) != OK)
		return ;
	if (set_mutex_status(&philo->philo_mutex, LOCK_MTX) != OK)
	{
		set_mutex_status(&philo->philo_mutex, UNLOCK_MTX);
		return;
	}
	if (philo->is_full)
	{
		set_mutex_status(&philo->philo_mutex, UNLOCK_MTX);
		return ;
	}
	if (set_mutex_status(&philo->philo_mutex, UNLOCK_MTX) != OK)
		return;
	if (set_mutex_status(&program->print_mutex, LOCK_MTX) != OK)
	{
		set_mutex_status(&program->print_mutex, UNLOCK_MTX);
		return ;
	}
	//ACCIONES QUE HAGA EL PRINT.
	select_case_to_print(program, philo, routine, time_passed);

	if (set_mutex_status(&program->print_mutex, UNLOCK_MTX) != OK)
		return ;
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_time_ms();
	while ((( (size_t)get_time_ms() - start) < milliseconds))
		usleep(500);
	return (0);
}