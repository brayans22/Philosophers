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
        if (start_program(program) != OK)
            return (ERROR);
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