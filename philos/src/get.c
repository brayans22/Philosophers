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
* POST: Obtenemos el valor del booleano evitando el data race.
*/
int get_is_end(t_program *program)
{
    int is_e;
    set_mutex_status(&program->end_mutex, LOCK_MTX);
	is_e = program->is_end;
	set_mutex_status(&program->end_mutex, UNLOCK_MTX);
    return (is_e);
}

/*
* PRE: -
* POST: Obtenemos el valor del total de los philos que estan llenos, evitando el data race.
*/
int get_total_philos_full(t_program *program)
{
    int total;
    set_mutex_status(&program->eat_mutex, LOCK_MTX);
    total = program->count_philos_full;
set_mutex_status(&program->eat_mutex, UNLOCK_MTX);
    return (total);
}

