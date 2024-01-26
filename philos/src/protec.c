#include "../headers/philosopher.h"

int set_mutex_status(pthread_mutex_t *mutex, int mode)
{
    int status;

    status = OK;
    if (mode == LOCK_MTX)
        status = pthread_mutex_lock(mutex);
    else if (mode == UNLOCK_MTX)
        status = pthread_mutex_unlock(mutex);
    else if (mode == INIT_MTX)
        status = pthread_mutex_init(mutex, NULL);
    else if (mode == DESTROY_MTX)
        status = pthread_mutex_destroy(mutex);
    else
        return (ft_putendl_fd(MESSAGE_ERROR_INVALID_MODE_MUTEX, 2), ERROR);
    return (status);
}

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