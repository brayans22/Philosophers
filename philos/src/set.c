#include "../headers/philosopher.h"

/*
* PRE: -
* POST: Cambia el thread segun el mode, y devuelve el estado de la operacion
*       Los status posibles son los siguientes
*       ERROR: Si el mode es incorrecto | o si falla alguna funcion de pthread
*       OK:    Si todo sale correctamente.
*/
int set_thread(pthread_t *thread, int mode, void *(*f_thread)(void * data))
{
    int status;

    if (!thread)
        return (ft_putendl_fd(MESSAGE_ERROR_THREAD, 2), ERROR);
    if (!f_thread)
        return (free(thread), ERROR);
    status = OK;
    if (mode == CREATE_THREAD)
        status = protect_thread(pthread_create(thread, NULL, f_thread, NULL));
    else if (mode == JOIN_THREAD)
        status = protect_thread(pthread_join(*thread, NULL));
    else if (mode == DETACH_THREAD)
        status = protect_thread(pthread_detach(*thread));
    else
        return (ft_putendl_fd(MESSAGE_ERROR_INVALID_MODE_THREAD, 2), ERROR);
    return (status);
}

/*
* PRE: -
* POST: Cambia el mutex segun el mode, y devuelve el estado de la operacion
*       Los status posibles son los siguientes
*       ERROR: Si el mode es incorrecto | o si falla alguna funcion de pthread_mutex
*       OK:    Si todo sale correctamente.
*/
int set_mutex_status(pthread_mutex_t *mutex, int mode)
{
    int status;

    if (!mutex)
        return (ft_putendl_fd(MESSAGE_ERROR_MUTEX, 2), ERROR);
    status = OK;
    if (mode == LOCK_MTX)
        status = protect_mutex(pthread_mutex_lock(mutex));
    else if (mode == UNLOCK_MTX)
        status = protect_mutex(pthread_mutex_unlock(mutex));
    else if (mode == INIT_MTX)
        status = protect_mutex(pthread_mutex_init(mutex, NULL));
    else if (mode == DESTROY_MTX)
        status = protect_mutex(pthread_mutex_destroy(mutex));
    else
        return (ft_putendl_fd(MESSAGE_ERROR_INVALID_MODE_MUTEX, 2), ERROR);
    
    return (status);
}