#include "../headers/philosopher.h"

int main(int argc, char **argv)
{
    if ((argc == 5 || argc == 6) && are_valid_arguments(argv))
    {
        
    }
    else
        ft_putendl_fd(ERROR_INVALID_ARGUMENTS, 2);

    return (0);
}