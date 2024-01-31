#include "../headers/philosopher.h"

/*
 * Pre: -
 * Post: Lleva acabo la rutina para 1 philosopher.
*/
static void case_one_philo(t_program *program)
{
    program->time_start = get_time_ms();
	print_simulation(program, &program->philos[0], TAKE_A_FORK);
    print_simulation(program, &program->philos[0], TAKE_A_FORK);
    ft_usleep(program->time_to_eat);
    print_simulation(program, &program->philos[0], SLEEPING);
    ft_usleep(program->time_to_sleep);
    print_simulation(program, &program->philos[0], THINKING);
    ft_usleep(program->time_to_die);
    print_simulation(program, &program->philos[0], DIED);
}

/*
 * Pre: -
 * Post: Lleva acabo la rutina para > 1 philosopher.
*/
static int case_more_than_one_philo(t_program *program)
{
    if(start_program(program) != OK)
        return (1);
    if(ft_clean_program(program) != OK)
        return (1);
    return (0);
}

/*
 * Pre: -
 * Post: Lleva acabo todos los procesos necesarios para el programa.
*/
int wrapper_philosophers(int argc, char **argv)
{
    t_program *program;

    program = get_malloc_memory(sizeof(t_program));
    if (!program)
        return (ERROR);
    if ((argc == 5 || argc == 6))
    {
        if (parser_arguments_to_program(program, argv) != OK)
            return (ERROR);
        if (init_program(program) != OK)
            return (ERROR);
        if (program->total_philos == 1)
            return (case_one_philo(program), 0);
        else
            return (case_more_than_one_philo(program));
    }
    return (free(program), ft_putendl_fd(MESSAGE_ERROR_INVALID_ARGUMENTS, 2), ERROR);
}