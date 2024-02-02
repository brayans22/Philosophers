#include "../headers/philosopher.h"

/*
* PRE: -
* POST: Muestra un mensaje por terminal de error (si es que ocurrer) devolviendo estado de error,
*       En caso contrario, no imprime ningun mensaje y devuelve un estado OK
*       Los estados posibles son:
*       OK:    Si todo sale correctamente.
*       EINVAL:     The value specified by atr is invalid (create, detach, join)
*       EPERM:      The current thread does not hold a lock on mutex (unlock)
*       EDEADLK:    A deadlock would occur if the thread blocked waiting for mutex. (lock)
*       ENOMEM:     The process cannot allocate enough memory to create another mutex. (init)
*       EBUSY:      Mutex is locked. (destroy)
*/
int protect_mutex(int mutex_return)
{
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
    return (OK);
}

/*
* PRE: -
* POST: Muestra un mensaje por terminal de error (si es que ocurrer) devolviendo estado de error,
*       En caso contrario, no imprime ningun mensaje y devuelve un estado OK
*       Los estados posibles son:
*       OK:         Si todo sale correctamente.
*       EINVAL:     The value specified by attr is invalid. (create | detach | join)
*       EPERM:      The caller does not have appropriate permission (create | join)
*       EDEADLK:    A deadlock was detected (join)
*       EAGAIN:     The system lacked the necessary resources to create another thread (create)
*       ESRCH:      No thread with the ID thread could be found. (detach | join)
*/
int protect_thread(int thread_return)
{
    if (thread_return == EAGAIN)
        return (ft_putendl_fd(MESSAGE_ERROR_THREAD_EAGAIN, 2), ERROR);
    else if (thread_return == EPERM)
        return (ft_putendl_fd(MESSAGE_ERROR_THREAD_EPERM, 2), ERROR);
    else if (thread_return == EDEADLK)
        return (ft_putendl_fd(MESSAGE_ERROR_THREAD_EDEADLK, 2), ERROR);
    else if (thread_return == ESRCH)
        return (ft_putendl_fd(MESSAGE_ERROR_THREAD_ESRCH, 2), ERROR);
    else if (thread_return == EINVAL)
        return (ft_putendl_fd(MESSAGE_ERROR_THREAD_EINVAL, 2), ERROR);
    return (OK);
}
