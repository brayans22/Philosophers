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