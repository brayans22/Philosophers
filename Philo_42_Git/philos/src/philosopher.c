/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsaiago- <bsaiago-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 00:29:40 by bsaiago-          #+#    #+#             */
/*   Updated: 2024/02/04 18:37:22 by bsaiago-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosopher.h"

void	case_one_philo(t_program *program)
{
	program->time_start = get_time_ms();
	print_simulation(program, &program->philos[0], TAKE_A_FORK);
	ft_usleep(program->time_to_die);
	print_simulation(program, &program->philos[0], DEAD);
}

int	wrapper_philosophers(int argc, char **argv)
{
	t_program	*program;
	int			exit;

	exit = 1;
	program = get_malloc_memory(sizeof(t_program));
	if (!program)
		return (exit);
	if ((argc == 5 || argc == 6))
	{
		if (parser_arguments_to_program(program, argv) != OK)
			return (exit);
		if (init_program(program) != OK)
			return (exit);
		if (program->total_philos > 1)
		{
			if (start_program(program) != OK)
				return (exit);
		}
		else
			case_one_philo(program);
		if (free_program(program) != OK)
			return (exit);
		return (!exit);
	}
	return (ft_putendl_fd(MESSAGE_ERROR_INVALID_ARGUMENTS, 2), exit);
}

int	main(int argc, char **argv)
{
	return (wrapper_philosophers(argc, argv));
}
