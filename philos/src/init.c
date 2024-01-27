#include "../headers/philosopher.h"


/* EN DESARROLLO, manejar error
static int is_valid_init_philos()
{
    int i;

    i = -1;
    program->philos = get_malloc_memory(sizeof(t_philo) * program->total_philos);
    if (!program->philos)
        return (FALSE);
}
*/

static int is_valid_init_forks(t_fork *forks, long total_philos)
{
    int i;

    i = -1;
    forks = get_malloc_memory(sizeof(t_fork) * total_philos);
    if (!forks)
        return (FALSE);
    while (++i < total_philos)
    {
        if (set_mutex_status(&(forks[i].fork_thread_mtx), INIT_MTX) != OK)
            return (FALSE);
        forks[i].id = i;
    }
    return (TRUE);
}

static int is_valid_init_program(t_program *program)
{
    program->time_start = 0;
    program->is_end = FALSE;
    if (!is_valid_init_forks(program->forks, program->total_philos))
        return (FALSE);
    //if (!is_valid_init_philos(program->total_philo))
    //      return (free(program->forks), ERROR);
    return (TRUE);
}

int init_program(t_program *program)
{
    if (!is_valid_init_program(program))
        return (ERROR);
    return (OK);
} 