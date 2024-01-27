#include "../headers/philosopher.h"

int main(int argc, char **argv)
{
    t_program program;
    if ((argc == 5 || argc == 6))
    {
        if (parser_arguments_to_program(&program, argv) != OK)
            return (ERROR);
        if (init_program(&program) != OK)
            return (ERROR);
    }
    else
        return (ft_putendl_fd(MESSAGE_ERROR_INVALID_ARGUMENTS, 2), ERROR);
    return (0);
}