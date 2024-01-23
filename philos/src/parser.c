#include "../headers/philosopher.h"

static int	ft_strlen_nb(char *str)
{
	int	len;
	int	start;

	len = 0;
	start = 0;
	while (str[start] == '0' && str[start])
		start++;
	while (str[start++])
		len++;
	return (len);
}

static long	ft_atol(const char *str)
{
	long		sign;
	long		nb;

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

static int	is_valid_number(char *nb)
{
	int	i;

	i = 0;
	if (nb[0] == '-')
		i++;
	while (nb[i])
	{
		if (nb[i] == '-')
			return (0);
		i++;
	}
	return (1);
}

static int	is_alpha_num(char *nb)
{
	int	i;

	i = 0;
	if (!nb)
		return (0);
	if (nb[0] == '-' && (nb[1] >= '0' && nb[1] <= '9'))
		i++;
	while (nb[i])
	{
		if (!(nb[i] >= '0' && nb[i] <= '9'))
			return (0);
		i++;
	}
	if (i == 0)
		return (0);
	return (1);
}

int is_valid_arguments(char **arguments)
{
    int status;
    int i;

    status = 0;
    i = 0;
    if (!*arguments || !arguments)
		return (0);
    while (arguments[++i] && is_v)
    {
		tmp = ft_atol(arguments[i]);
		if (!is_valid_number(arguments[i]))
			is_v = 0;
		if (!is_alpha_num(arguments[i]))
			is_v = 0;
	    	/*
	    	if (tmp < MIN_INT || tmp > MAX_INT \
				|| (ft_strlen_nb(argv[i]) > 10 && argv[i][0] != '-') \
			|| (ft_strlen_nb(argv[i]) > 11 && argv[i][0] == '-'))
			is_v = 0;
		*/
	}
	if (!is_v)
		ft_putendl_fd("Error\n Invalid Arguments!\n", 2);
    return (1);
}
