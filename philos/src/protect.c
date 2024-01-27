#include "../headers/philosopher.h"

/*
* PRE: -
* POST: Alloca un bloque de memoria con malloc y lo llena de '\0' si todo sale correctamente,
*       En caso de error, devuelve NULL y muestra un mensaje por terminal indicando un error.
*/
void    *get_malloc_memory(size_t bytes_alloc)
{
    void    *mem;

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

/*
* PRE: -
* POST: Muestra un mensaje por terminal de error (si es que ocurrer) devolviendo estado de error,
*       En caso contrario, no imprime ningun mensaje y devuelve un estado OK
*       Los estados posibles son:
*           OK:    Si todo sale correctamente.
*           EINVAL:     The value specified by atr is invalid (create, detach, join)
*           EPERM:      The current thread does not hold a lock on mutex (unlock)
*           EDEADLK:    A deadlock would occur if the thread blocked waiting for mutex. (lock)
*           ENOMEM:     The process cannot allocate enough memory to create another mutex. (init)
*           EBUSY:      Mutex is locked. (destroy)
*/
static int protect_mutex(int mutex_return)
{
    /*
    if (mutex_return == EINVAL)
        return (ft_putendl_fd(MESSAGE_ERROR_MUTEX_EINVAL, 2), ERROR);
    else if (mutex_return == EPERM)
        return (ft_putendl_fd(MESSAGE_ERROR_MUTEX_EPERM, 2), ERROR);
    else if (mutex_return == EDEADLK)
        return (ft_putendl_fd(MESSAGE_ERROR_MUTEX_EDEADLK, 2), ERROR);
    else if (mutex_return == ENOMEM)
        return (ft_putendl_fd(MESSAGE_ERROR_MUTEX_ENOMEM, 2), ERROR);
    else if (mutex_return == EBUSY)
        return (ft_putendl_fd(MESSAGE_ERROR_MUTEX_EBUSY, 2), ERROR);
    */
    /* Pongo esta linea para que no me tire error al compilar por no usar el parametro de la funcion */
        if (mutex_return != OK)
        return (ERROR);
    return (OK);
}

/*
* PRE: -
* POST: Cambia el mutex segun el mode, y devuelve el estado de la operacion
*       Los status posibles son los siguientes
*           ERROR: Si el mode es incorrecto | o si falla alguna funcion de pthread_mutex
*           OK:    Si todo sale correctamente.
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

/*
* PRE: -
* POST: Muestra un mensaje por terminal de error (si es que ocurrer) devolviendo estado de error,
*       En caso contrario, no imprime ningun mensaje y devuelve un estado OK
*       Los estados posibles son:
*           OK:         Si todo sale correctamente.
*           EINVAL:     The value specified by attr is invalid. (create | detach | join)
*           EPERM:      The caller does not have appropriate permission (create | join)
*           EDEADLK:    A deadlock was detected (join)
*           EAGAIN:     The system lacked the necessary resources to create another thread (create)
*           ESRCH:      No thread with the ID thread could be found. (detach | join)
*/
static int protect_thread(int thread_return)
{
    /*
    if (thread_return == EAGAIN)
        return (ft_putendl_fd(MESSAGE_ERROR_THREAD_EAGAIN, 2), ERROR);
    else if (thread_return == EPERM)
        return (ft_putendl_fd(MESSAGE_ERROR_THREAD_EPERM, 2), ERROR);
    else if (thread_return == EDEADLK)
        return (ft_putendl_fd(MESSAGE_ERROR_THREAD_EDEADLK, 2), ERROR);
    else if (thread_return == ESRCH)
        return (ft_putendl_fd(MESSAGE_ERROR_THREAD_ESRCH, 2), ERROR);
    else if (thread_return == EINVAL)
        return (ft_putendl_fd(MESSAGE_ERROR_THREAD_EBUSY, 2), ERROR);
    */
    
    /*  Pongo esta linea para que no me tire error al compilar por no usar el parametro de la funcion */
        if (thread_return != OK)
        return (ERROR);
    return (OK);
}

/*
* PRE: -
* POST: Cambia el thread segun el mode, y devuelve el estado de la operacion
*       Los status posibles son los siguientes
*           ERROR: Si el mode es incorrecto | o si falla alguna funcion de pthread
*           OK:    Si todo sale correctamente.
*/
int get_thread(pthread_t *thread, int mode, void *(*f_thread)(void * data))
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
