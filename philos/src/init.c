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
        // Proger si falla mutex (EINVAL) | cambiar esto de error
        if (set_mutex_status(&(forks[i].fork_thread_mtx), INIT_MTX) == ERROR)
            return (ft_putendl_fd(MESSAGE_ERROR_MUTEX_INIT, 2), FALSE);
        forks[i].id = i;
    }
    return (TRUE);
}

static int is_valid_init_program(t_program *program, char **arguments)
{
    program->time_start = 0;
    program->limits_meals = 0;
    program->is_end = FALSE;
    program->total_philos = ft_atol(arguments[1]); 
    program->time_to_die = ft_atol(arguments[2]);
    program->time_to_eat = ft_atol(arguments[3]);
    program->time_to_sleep = ft_atol(arguments[4]);
    if (arguments[5])
        program->limits_meals = ft_atol(arguments[5]);
    if (!is_valid_init_forks(program->forks, program->total_philos))
        return (FALSE);
    //if (!is_valid_init_philos(program->total_philo))
    //      return (free(program->forks), ERROR);
    return (TRUE);
}

int init_program(t_program *program, char **arguments)
{
    if (!is_valid_init_program(program, arguments))
        return (ERROR);
    return (OK);
} 