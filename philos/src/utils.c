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

/*
* PRE: No puede ser nulo s1
* POST: Devuelve la longitud del string
*/
int	ft_strlen(const char *s1)
{
	int	i;

	i = -1;
	while (s1[i])
		++i;
	return (i);
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

/*
* PRE: -
* POST: Convierte un array str to integer.
*/
long	ft_atol(const char *str)
{
	long	sign;
	long	nb;

	sign = 1;
	nb = 0;
	while (*str == '\t' || *str == '\v' || *str == '\f' || \
		*str == '\n' || *str == ' ' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (*str >= MIN_DIGIT_CHAR && *str <= MAX_DIGIT_CHAR)
	{
		nb = nb * 10 + *str - '0';
		str++;
	}
	return (nb * sign);
}