#ifndef PHILOSOPHER_H_
# define PHILOSOPHER_H_

/* INCLUDES */
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include "philosopher.h"

/* CONSTANTS */
# define MESSAGE_ERROR_INVALID_ARGUMENTS "Error\n Invalid Arguments!\n"
# define MESSAGE_TAKEN_A_FORK "milisegundos (ms) has taken a fork\n"
# define MESSAGE_IS_EATING "milisegundos (ms) is eating\n"
# define MESSAGE_IS_SLEEPING "milisegundos (ms) is sleeping\n"
# define MESSAGE_IS_THINKING "milisegundos (ms) is thinking\n"
# define MESSAGE_IS_DIED "milisegundos (ms) is died\n"
# define ERROR -1


/* STRUCTS */

/* PROTOYPES */
int	  ft_strlen(const char *s1);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int nb, int fd); 
