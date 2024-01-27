#include "../headers/philosopher.h"
/*

long    last_meal_time;
    pthread_t thread_id;
    t_fork *left_fork;
    t_fork *right_fork;
    t_program *program;
*/

/*
* PRE: -
* POST: Asigna un tenedor a un philo dependiendo de si su id es par o impar devolviendo el estado
*       De la operacion
*       OK:     La asignacion del tenedor al philo fue correcta.
*       ERROR:  La asignacion del tenedor al philo fue incorrecta.
*/
static int assign_fork_to_philo(t_philo *philo, t_fork *forks, int index_philo, int total_philos)
{
    if (!philo || !forks)
        return (ERROR);
    // is odd
    if (philo->id % 2 == 1)
    {
        philo->right_fork = &forks[index_philo];
        philo->left_fork = &forks[(index_philo + 1) % total_philos];
    }
    else
    {
        philo->right_fork = &forks[(index_philo + 1) % total_philos];
        philo->left_fork = &forks[index_philo];
    }
    return (OK);
}

/*
* PRE: -
* POST: Chequea la inicializacion de los philos, cargando sus campos y devolviendo el estado 
*       de la validez del proceso, true si salio bien, false caso contrario.
*       OK:     La asignacion del philo fue correcta.
*       ERROR:  La asignacion del philo fue incorrecta.
*/
static int init_philos(t_philo *philos, long total_philos, t_fork *forks)
{
    int i;

    i = -1;
    philos = get_malloc_memory(sizeof(t_philo) * total_philos);
    if (!philos)
        return (ERROR);
    if (!forks)
        return (free(philos), ERROR);
    while (++i < total_philos)
    {
        philos[i].is_full = FALSE;
        philos[i].id = i + 1;
        philos[i].counter_meals = 0;
        // Aun no comio, entonces lo inicializo con un valor que indique eso.
        philos[i].last_meal_time = NOT_EAT_YET; 
        if (assign_fork_to_philo(&philos[i], forks, i, total_philos) != OK)
            return (free(philos), ERROR);
    }
    return (OK);
}

/*
* PRE: -
* POST: Chequea la inicializacion de los forks, cargando sus campos y devolviendo el estado 
*       de la validez del proceso, true si salio bien, false caso contrario.
*       OK:     La asignacion del tenedor al philo fue correcta.
*       ERROR:  La asignacion del tenedor al philo fue incorrecta.
*/
static int init_forks(t_fork *forks, long total_philos)
{
    int i;

    i = -1;
    forks = get_malloc_memory(sizeof(t_fork) * total_philos);
    if (!forks)
        return (ERROR);
    while (++i < total_philos)
    {
        if (set_mutex_status(&(forks[i].fork_thread_mtx), INIT_MTX) != OK)
            return(free(forks), ERROR);
        forks[i].id = i;
    }
    return (OK);
}

/*
* PRE: -
* POST: la inicializacion del programa, devolviendo el estado de la operacion
*       OK:     La inicializacion del programa fue correcta.
*       ERROR:  La inicializacion del programa fue incorrecta.
*/
static int wrapper_init_program(t_program *program)
{
    if (!program)
        return (ERROR);
    program->time_start = 0;
    program->is_end = FALSE;
    if (!init_forks(program->forks, program->total_philos))
        return (FALSE);
    if (!init_philos(program->philos, program->total_philos, program->forks))
        return (free(program->forks), ERROR);
    return (TRUE);
}

/*
* PRE: -
* POST: la inicializacion del programa, devolviendo el estado de la operacion
*       OK:     La inicializacion del programa fue correcta.
*       ERROR:  La inicializacion del programa fue incorrecta.
*/
int init_program(t_program *program)
{
    return (wrapper_init_program(program));
} 