#include "../headers/philosopher.h"

/*
 * Pre: -
 * Post: Realiza la rutina de 1 philosopher.
*/
static void case_one_philo(t_program *program)
{
    program->time_start = get_time_ms();
    print_simulation(program, &program->philos[0], TAKE_A_FORK, 0);
	ft_usleep(program->time_to_die);
	print_simulation(program, &program->philos[0], DEAD, program->time_to_die);
}

/*
 * Pre: -
 * Post: Lleva acabo todos los procesos necesarios para el programa.
*/
static int wrapper_philosophers(int argc, char **argv)
{
    t_program *program;
    int exit;

    program = get_malloc_memory(sizeof(t_program));
    exit = 1;
    if (!program)
        return (exit);
    if ((argc == 5 || argc == 6))
    {
        if (parser_arguments_to_program(program, argv) != OK)
            return (exit);
        if (init_program(program) != OK)
            return (exit);
        if (program->total_philos > 1)
        {
            if (start_program(program) != OK)
                return (exit);
        }
        else
            case_one_philo(program);
        if(free_program(program) != OK)
            return (exit);
        return (!exit);
    }
    return (ft_putendl_fd(MESSAGE_ERROR_INVALID_ARGUMENTS, 2), exit);
}

int main(int argc, char **argv)
{
    return (wrapper_philosophers(argc, argv));
}