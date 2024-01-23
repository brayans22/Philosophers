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

#include "../headers/philosophers.h"

void	ft_putstr_fd(char *s, int fd)
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

int	ft_atoi(const char *str)
{
	int	sign;
	int	nb;

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
	while (*str >= '0' && *str <= '9')
	{
		nb = nb * 10 + *str - '0';
		str++;
	}
	return (nb * sign);
}

int	ft_strlen(const char *s1)
{
	int	i;

	i = -1;
	while (s1[i])
		++i;
	return (i);
}

void	ft_putendl_fd(char *s, int fd)
{
	char	*first;

	first = s;
	if (fd == -1)
		return ;
	while (*s)
	{
		write(fd, s, 1);
		s++;
	}
	write(fd, "\n", 1);
	s = first;
}

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