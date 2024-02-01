#include "../headers/philosopher.h"

/*
 * Pre: -
 * Post: Lleva acabo todos los procesos necesarios para el programa.
*/
int wrapper_philosophers(int argc, char **argv)
{
    t_program *program;

    program = get_malloc_memory(sizeof(t_program));
    if (!program)
        return (1);
    if ((argc == 5 || argc == 6))
    {
        if (parser_arguments_to_program(program, argv) != OK)
            return (1);
        if (init_program(program) != OK)
            return (1);
        if(start_program(program) != OK)
            return (1);
        if(ft_clean_program(program) != OK)
            return (1);
        return (0);
    }
    return (free(program), ft_putendl_fd(MESSAGE_ERROR_INVALID_ARGUMENTS, 2), ERROR);
}