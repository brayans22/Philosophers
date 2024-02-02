#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

/* INCLUDES */
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <pthread.h>
# include <time.h>
# include <sys/time.h>
# include "philosopher.h"
# include <limits.h>

/* CONSTANTS */
# define MIN_DIGIT_CHAR                 '0'
# define MAX_DIGIT_CHAR                 '9'
# define NULL_STR                       '\0'
# define MAX_INT                        2147483647
# define MIN_INT                        -2147483648

# define MESSAGE_ERROR_MUTEX                "Error\nMutex throw exception\n"
# define MESSAGE_ERROR_INVALID_MODE_MUTEX   "Error\nInvalid mode mutex\n"
# define MESSAGE_MORE_THAN_ZERO             "Error\nArgument has to be more than zero\n"
# define MESSAGE_ERROR_MUTEX_EINVAL         "Error\nMutex throw exception (The value specified by attr is invalid.)\n"
# define MESSAGE_ERROR_MUTEX_EPERM          "Error\nMutex throw exception (The current thread does not hold a lock on mutex.)\n"
# define MESSAGE_ERROR_MUTEX_ENOMEM         "Error\nMutex throw exception (The process cannot allocate enough memory to create another mutex)\n"
# define MESSAGE_ERROR_MUTEX_EDEADLK        "Error\nMutex throw exception (A deadlock would ocurr if the thread blocked waiting for mutex.)\n"
# define MESSAGE_ERROR_MUTEX_EBUSY          "Error\nMutex throw exception (Mutex is locked)\n"
# define MESSAGE_ERROR_THREAD               "Error\nThread throw exception\n"
# define MESSAGE_ERROR_THREAD_EAGAIN        "Error\nThread throw exception (The system lacked the necessary resources to create another thread)\n"
# define MESSAGE_ERROR_THREAD_EPERM         "Error\nThread throw exception (The caller does not have appropiate permission)\n"
# define MESSAGE_ERROR_THREAD_ESRCH         "Error\nThread throw exception (No thread with the ID thread could be found.)\n"
# define MESSAGE_ERROR_THREAD_EDEADLK       "Error\nThread throw exception (A deadlock was detected)\n"
# define MESSAGE_ERROR_THREAD_EINVAL         "Error\nThread throw exception (The value specified by attr is invalid.)\n"
# define MESSAGE_ERROR_INVALID_MODE_THREAD   "Error\nInvalid mode thread\n"
# define MESSAGE_ERROR_NOT_NUMERIC_ARGUMENT "Error\nArguments has to be positive numbers!\n"
# define MESSAGE_ERROR_OUT_OF_INT_LIMIT     "Error\nArguments has to respect the int limits\n"
# define MESSAGE_ERROR_MALLOC               "Error\nMalloc allocation fails\n"
# define MESSAGE_ERROR_MEMSET               "Error\nMemset fails\n"
# define MESSAGE_ERROR_INVALID_ARGUMENTS "Error Invalid Arguments!\nUsage: \
number_of_philosophers time_to_die time_to_eat time_to_sleep \
[number_of_times_each_philosopher_must_eat]\n\
Example: ./philo 5 600 500 400 [5]\n"

# define ERROR               -1
# define NOT_EAT_YET         -9
# define EMPTY               -2
# define OK                  2
# define TRUE                1
# define FALSE               0
# define INIT_MTX            0
# define LOCK_MTX            1
# define UNLOCK_MTX          2
# define DESTROY_MTX         3
# define CREATE_THREAD      -3
# define JOIN_THREAD        -2
# define DETACH_THREAD      -1
# define TAKE_A_FORK        -10
# define TAKE_FIRST_FORK    -15
# define EATING             -11
# define SLEEPING           -12
# define THINKING           -13
# define DEAD               -14

/* STRUCTS */
typedef struct s_fork
{
    pthread_mutex_t fork_thread_mtx;
    int id;
} t_fork;

typedef struct s_philo t_philo;

typedef struct s_program
{
    int     total_philos;
    long    time_to_die;
    long    time_to_eat;
    long    time_to_sleep;
    long    limits_meals;
    int     count_philos_full;
    int is_end;
    long    time_start;
    t_philo *philos;
    t_fork  *forks;
    pthread_t thread_monitor;
    pthread_mutex_t print_mutex;
    pthread_mutex_t end_mutex;
    pthread_mutex_t count_philos_mutex;
    pthread_mutex_t get_time_mutex;
}t_program;

struct s_philo
{
    int id;
    int is_full;
    int counter_meals;
    long last_meal_time;
    pthread_t thread_id;
    t_fork *left_fork;
    t_fork *right_fork;
    t_program *program;
};

/* PARSER.C */
int	    parser_arguments_to_program(t_program *program, char **arguments);

/* INIT.C */
int     init_program(t_program *program);

/* UTILS.C */
void	ft_putendl_fd(char *s, int fd);
long get_time_ms();
void print_simulation(t_program *program, t_philo *philo, int routine);
void	ft_usleep(long int time_in_ms);

/* SET.C */
int     set_mutex_status(pthread_mutex_t *mutex, int mode);
int     set_thread(pthread_t *thread, int mode, void *(*f_thread)(void *data), void *data_t);

/* GET.C */
int get_is_end(t_program *program);
int get_total_philos_full(t_program *program);
void    *get_malloc_memory(size_t bytes_alloc);

/* PROTECT.C */
int     protect_mutex(int mutex_return);
int     protect_thread(int thread_return);

/* GET.C */
int     start_program(t_program *program);
int	    free_program(t_program *program);
void	*monitor_program(void *data);
void *philo_routine(void *data);
int wrapper_philosophers(int argc, char **argv);
void    set_total_philos_full(t_program *program);
void    set_is_end(t_program *program);



#endif 