/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsaiago- <bsaiago-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 00:41:18 by bsaiago-          #+#    #+#             */
/*   Updated: 2024/02/04 22:28:10 by bsaiago-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosopher.h"

void	set_bool(pthread_mutex_t mtx, int *value_bool)
{
	pthread_mutex_lock(&mtx);
	(*value_bool) = !(*value_bool);
	pthread_mutex_unlock(&mtx);
}

void	set_int(pthread_mutex_t mtx, int *value_int, int set)
{
	pthread_mutex_lock(&mtx);
	(*value_int) = set;
	pthread_mutex_unlock(&mtx);
}

void	set_long(pthread_mutex_t mtx, long *value_long, long set)
{
	pthread_mutex_lock(&mtx);
	(*value_long) = set;
	pthread_mutex_unlock(&mtx);
}

void	increase_long(pthread_mutex_t mtx, long *value_long, long increase)
{
	pthread_mutex_lock(&mtx);
	(*value_long) += increase;
	pthread_mutex_unlock(&mtx);
}
