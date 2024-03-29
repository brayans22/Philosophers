/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:50:54 by brayan            #+#    #+#             */
/*   Updated: 2024/02/06 20:51:12 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosopher.h"

/*
* PRE: -
* POST: Cambia el thread segun el mode, y devuelve el estado de la operacion
*       Los status posibles son los siguientes
*       ERROR: Si el mode es incorrecto | o si falla alguna funcion de pthread
*       OK:    Si todo sale correctamente.
*/
int	set_thread(pthread_t *thread, int mode \
, void *(*f_thread)(void *data), void *data_t)
{
	int	status;

	if (!thread)
		return (ft_putendl_fd(MESSAGE_ERROR_THREAD, 2), ERROR);
	status = OK;
	if (mode == CREATE_THREAD)
		pthread_create(thread, NULL, f_thread, data_t);
	else if (mode == JOIN_THREAD)
		pthread_join(*thread, NULL);
	else if (mode == DETACH_THREAD)
		pthread_detach(*thread);
	else
		return (ft_putendl_fd(MESSAGE_ERROR_INVALID_MODE_THREAD, 2), ERROR);
	return (status);
}

/*
* PRE: -
* POST: Cambia el mutex segun el mode, y devuelve el estado de la operacion
*       Los status posibles son los siguientes
*       ERROR: Si el mode es incorrecto | o si falla alguna funcion 
*		de pthread_mutex
*       OK:    Si todo sale correctamente.
*/
int	set_mutex_status(pthread_mutex_t *mutex, int mode)
{
	if (!mutex)
		return (ft_putendl_fd(MESSAGE_ERROR_MUTEX, 2), ERROR);
	if (mode == LOCK_MTX)
		pthread_mutex_lock(mutex);
	else if (mode == UNLOCK_MTX)
		pthread_mutex_unlock(mutex);
	else if (mode == INIT_MTX)
		pthread_mutex_init(mutex, NULL);
	else if (mode == DESTROY_MTX)
		pthread_mutex_destroy(mutex);
	else
		return (ft_putendl_fd(MESSAGE_ERROR_INVALID_MODE_MUTEX, 2), ERROR);
	return (OK);
}

/*
* PRE: -
* POST: Obtenemos el valor del booleano evitando el data race.
*/
void	set_is_end(t_program *program)
{
	set_mutex_status(&program->end_mutex, LOCK_MTX);
	program->is_end = TRUE;
	set_mutex_status(&program->end_mutex, UNLOCK_MTX);
}

/*
* PRE: -
* POST: Aumentamos 1 al total de philos full, evitando el data race.
*/
void	set_total_philos_full(t_program *program)
{
	set_mutex_status(&program->count_philos_mutex, LOCK_MTX);
	program->count_philos_full++;
	set_mutex_status(&program->count_philos_mutex, UNLOCK_MTX);
}
