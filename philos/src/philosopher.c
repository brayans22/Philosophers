#include "../headers/philosopher.h"

static int wrapper_main(int argc, char **argv)
{
    t_program *program;

    program = get_malloc_memory(sizeof(t_program));
    if (!program)
        return (ERROR);
    else if ((argc == 5 || argc == 6))
    {
        if (parser_arguments_to_program(program, argv) != OK)
            return (ERROR);
        if (init_program(program) != OK)
            return (ERROR);
        if (program->total_philos == 1)
        {
            program->time_start = get_time_ms();
	        print_simulation(program, &program->philos[0], TAKE_A_FORK);
            print_simulation(program, &program->philos[0], TAKE_A_FORK);
            ft_usleep(program->time_to_eat);
            ft_usleep(program->time_to_sleep);
            print_simulation(program, &program->philos[0], SLEEPING);
            print_simulation(program, &program->philos[0], THINKING);
	        ft_usleep(program->time_to_die);
	        print_simulation(program, &program->philos[0], DIED);
        }
        else
        {
            if(start_program(program) != OK)
                return (ERROR);
        }
        if(ft_clean_program(program) != OK)
            return (ERROR);
        return (0);
    }
    return (free(program), ft_putendl_fd(MESSAGE_ERROR_INVALID_ARGUMENTS, 2), ERROR);
}

int main(int argc, char **argv)
{
    return (wrapper_main(argc, argv));
}