

int is_valid_arguments(char **arguments)
{
    int status;
    int i;

    status = 0;
    i = 0;
    if (!*arguments || !arguments)
		return (0);
    while (arguments[++i])
    {
		tmp = ft_atol(arguments[i]);
		if (!is_valid_number(arguments[i]))
			is_v = 0;
		if (!is_alpha_num(arguments[i]))
			is_v = 0;		if (tmp < MIN_INT || tmp > MAX_INT \
				|| (ft_strlen_nb(arguments[i]) > 10 && argv[i][0] != '-') \
			|| (ft_strlen_nb(argv[i]) > 11 && argv[i][0] == '-'))
			is_v = 0;
	}
	if (!is_v)
		write(2, "Error\n", 6);
    return (1);
}