/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsaiago- <bsaiago-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 21:15:37 by bsaiago-          #+#    #+#             */
/*   Updated: 2024/02/04 20:50:53 by bsaiago-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosopher.h"

void	*get_malloc_memory(size_t bytes_alloc)
{
	void	*mem;

	mem = (void *)malloc(bytes_alloc);
	if (!mem)
		return (ft_putendl_fd(MESSAGE_ERROR_MALLOC, 2), NULL);
	else
	{
		if (!memset(mem, NULL_STR, sizeof(bytes_alloc)))
			return (ft_putendl_fd(MESSAGE_ERROR_MEMSET, 2), NULL);
	}
	return (mem);
}

int	get_bool(pthread_mutex_t mtx, int value_bool)
{
	int	b;

	pthread_mutex_lock(&mtx);
	b = value_bool;
	pthread_mutex_unlock(&mtx);
	return (b);
}

int	get_int(pthread_mutex_t mtx, int value_int)
{
	int	b;

	pthread_mutex_lock(&mtx);
	b = value_int;
	pthread_mutex_unlock(&mtx);
	return (b);
}

long	get_long(pthread_mutex_t mtx, long value_long)
{
	long	b;

	pthread_mutex_lock(&mtx);
	b = value_long;
	pthread_mutex_unlock(&mtx);
	return (b);
}
