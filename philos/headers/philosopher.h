#ifndef PHILOSOPHER_H_
# define PHILOSOPHER_H_

/* INCLUDES */
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include "philosopher.h"

/* CONSTANTS */
# define ERROR_INVALID_ARGUMENTS "Error\n Invalid Arguments\n"
# define MESSAGE_TAKEN_A_FORK "has taken a fork\n"
# define MESSAGE_IS_EATING "is eating\n"
# define MESSAGE_IS_SLEEPING "is sleeping\n"
# define MESSAGE_IS_THINKING "is thinking\n"
# define MESSAGE_IS_DIED "is died\n"
  
int   ft_strlen_nb(char *str);
int		ft_atoi(const char *str);
void	ft_putstr_fd(char *s, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int nb, int fd); 
