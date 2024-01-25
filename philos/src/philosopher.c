#include "../headers/philosopher.h"

int main(int argc, char **argv)
{
    if ((argc == 5 || argc == 6))
    {
        if (parser_arguments(argv) != OK)
            return (ERROR);
    }
    else
        return (ft_putendl_fd(MESSAGE_ERROR_INVALID_ARGUMENTS, 2), ERROR);
    return (0);
}