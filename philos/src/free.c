#include "../headers/philosopher.h"

/*
 * PRE: -
 * POST: Libera la memoria usada en el programa (threads, mutex, structs...)
 */
int free_program(t_program *program)
{
	int i;

	if (program->total_philos > 1)
	{
		while (++i < program->total_philos)
			set_mutex_status(&program->forks[i].fork_thread_mtx, DESTROY_MTX);
	}
	set_mutex_status(&program->end_mutex, DESTROY_MTX);
	set_mutex_status(&program->get_time_mutex, DESTROY_MTX);
	set_mutex_status(&program->print_mutex, DESTROY_MTX);
	set_mutex_status(&program->count_philos_mutex, DESTROY_MTX);
    if (program->forks)
	    free(program->forks);
    if (program->philos)
	    free(program->philos);
	free(program);
	return (OK);
}