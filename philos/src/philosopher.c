#include "../headers/philosopher.h"

int main(int argc, char **argv)
{
    if ((argc == 5 || argc == 6))
    {
        if (parser_arguments(argv) == ERROR)
            ft_putendl_fd(ERROR_INVALID_ARGUMENTS, 2)
    }
    else
        ft_putendl_fd(ERROR_INVALID_ARGUMENTS, 2);
    return (0);
}