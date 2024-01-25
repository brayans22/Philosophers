#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

/* INCLUDES */
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include "philosopher.h"
# include <limits.h>

/* CONSTANTS */
# define MIN_DIGIT_CHAR                 '0'
# define MAX_DIGIT_CHAR                 '9'
# define MAX_INT                        2147483647
# define MIN_INT                        -2147483648

# define MESSAGE_ERROR_INVALID_ARGUMENTS "Error Invalid Arguments!\nUsage: \
number_of_philosophers time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n\
Example: ./philo 5 600 500 400 [5]\n"
# define MESSAGE_ERROR_NOT_NUMERIC_ARGUMENT "Error\nArguments has to be positive numbers!\n"
# define MESSAGE_ERROR_OUT_OF_INT_LIMIT     "Error\nArguments has to respect the int limits\n"
# define MESSAGE_ERROR_MILISECONDS          "Error\nTimestamp has to be major than > 60 ms\n"
# define MESSAGE_TAKEN_A_FORK "milisegundos (ms) has taken a fork\n"
# define MESSAGE_IS_EATING "milisegundos (ms) is eating\n"
# define MESSAGE_IS_SLEEPING "milisegundos (ms) is sleeping\n"
# define MESSAGE_IS_THINKING "milisegundos (ms) is thinking\n"
# define MESSAGE_IS_DIED "milisegundos (ms) is died\n"

# define ERROR -1
# define TRUE   1
# define OK     2
# define FALSE  0

/* STRUCTS */

/* PROTOYPES */
int	    parser_arguments(char **arguments);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int nb, int fd); 


#endif 