#include "../headers/philosopher.h"
#include "../headers/philosopher.h"

/*
* PRE: -
* POST: Convierte un array str to integer.
*/
static long	ft_atol(const char *str)
{
	long	sign;
	long	nb;

	sign = 1;
	nb = 0;
	while (*str == '\t' || *str == '\v' || *str == '\f' || \
		*str == '\n' || *str == ' ' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -sign;
		str++;
	}
	while (*str >= MIN_DIGIT_CHAR && *str <= MAX_DIGIT_CHAR)
	{
		nb = nb * 10 + *str - '0';
		str++;
	}
	return (nb * sign);
}

/*
* PRE: -
* POST: Devuelve la longitud del numero ignorando los 0 a la izquierda
*       Si el parametro es nulo, la longitud del numero se considera 0
*/
static int	ft_strlen_nb(char *str)
{
	int	len;
	int	start;

	if (!str)
		return (0);
	len = 0;
	start = 0;
	while (str[start] == '0' && str[start])
		start++;
	while (str[start++])
		len++;
	return (len);
}

/*
* PRE: El flag_ms_limit debe ser un valor entre 1 o 0
* POST: Valida el numero, chequeando las siguientes condiciones:
*       -> > 0 (Positivo)
*       -> sea un numero
*       -> Este en el rango de los integers [INT MAX - INT MIX]
*       -> Y que sea > 60 ms el timestamp
*/
static int	is_valid_argument(char *nb)
{
	int		i;
	long	tmp;

	if (!nb)
		return (ERROR);
	i = -1;
	while (nb[++i])
	{
		if (!(nb[i] >= MIN_DIGIT_CHAR && nb[i] <= MAX_DIGIT_CHAR))
			return (ft_putendl_fd(MESSAGE_ERROR_NOT_NUMERIC_ARGUMENT \
			, 2), FALSE);
	}
	tmp = ft_atol(nb);
	if (tmp < MIN_INT || tmp > MAX_INT \
		|| (ft_strlen_nb(nb) > 10 && nb[0] != '-') \
			|| (ft_strlen_nb(nb) > 11 && nb[0] == '-'))
		return (ft_putendl_fd(MESSAGE_ERROR_OUT_OF_INT_LIMIT, 2), FALSE);	
	if (tmp <= 0)
		return (ft_putendl_fd(MESSAGE_MORE_THAN_ZERO, 2), FALSE);
	return (TRUE);
}

/*
* PRE: -
* POST: Parsea los argumentos, agregandolos en el programa 
*	    y devuelve el status de la operacion
*       OK: Si todo salio en orden
*       ERROR: Si hubo algun error en el proceso
*/
static int	wrapper_parser_arguments_to_program(char **arguments \
, t_program *program)
{
	if (!is_valid_argument(arguments[1]) || !is_valid_argument(arguments[2]) \
		|| !is_valid_argument(arguments[3]) || !is_valid_argument(arguments[4]) \
		|| (arguments[5] && !is_valid_argument(arguments[5])))
		return (ERROR);
	program->total_philos = ft_atol(arguments[1]);
	program->time_to_die = ft_atol(arguments[2]);
	program->time_to_eat = ft_atol(arguments[3]);
	program->time_to_sleep = ft_atol(arguments[4]);
	if (arguments[5])
		program->limits_meals = ft_atol(arguments[5]);
	else
		program->limits_meals = EMPTY;
	return (OK);
}

/*
* PRE: -
* POST: Parsea los argumentos, agregandolos en el programa 
*       y devuelve el status de la operacion
*       OK: Si todo salio en orden
*       ERROR: Si hubo algun error en el proceso
*/
int	parser_arguments_to_program(t_program *program, char **arguments)
{
	if (!*arguments || !arguments || !program)
		return (ERROR);
	return (wrapper_parser_arguments_to_program(arguments, program));
}
