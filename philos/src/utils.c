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
* POST: Muestra un string s en la terminal.
*/
static void	ft_putstr_fd(char *s, int fd)
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
	s = first;
}


long long	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)(tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}


int	ft_clean_program(t_program *program)
{
	t_philo	*philo;
	int		i;

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
void	ft_putendl_fd(char *s, int fd)
{
	char	*first;

	first = s;
	if (fd == -1)
		return ;
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
	s = first;
}

/*
* PRE: -
* POST: Muestra un numero en la terminal.
*/
void	ft_putnbr_fd(int nb, int fd)
{
	int	n;

	if (nb == -2147483648)
	{
		write(fd, "-", 1);
		write(fd, "2", 1);
		ft_putnbr_fd(147483648, fd);
	}
	else if (nb < 0)
	{
		write(fd, "-", 1);
		ft_putnbr_fd(-nb, fd);
	}
	else if (nb > 9)
	{
		ft_putnbr_fd(nb / 10, fd);
		ft_putnbr_fd(nb % 10, fd);
	}
	else
	{
		n = nb + '0';
		write(fd, &n, 1);
	}
}
