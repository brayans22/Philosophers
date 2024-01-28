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


int	ft_usleep(useconds_t time)
{
	u_int64_t	start;
	start = get_time();
	while ((get_time() - start) < time)
		usleep(time / 10);
	return(0);
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
