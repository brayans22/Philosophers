/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brayan <brayan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 20:27:15 by brayan            #+#    #+#             */
/*   Updated: 2024/02/06 20:56:46 by brayan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/philosopher.h"

/*
 * Pre: -
 * Post: Realiza la rutina de 1 philosopher.
*/
static void	case_one_philo(t_program *program)
{
	program->time_start = get_time_ms();
	print_simulation(program, &program->philos[0], TAKE_A_FORK, 0);
	ft_usleep(program->time_to_die);
	print_simulation(program, &program->philos[0], DEAD, program->time_to_die);
}

/*
 * Pre: -
 * Post: Lleva acabo todos los procesos necesarios para el programa.
*/
static int	wrapper_philosophers(int argc, char **argv \
, t_program *program, int exit_status)
{
	if ((argc == 5 || argc == 6))
	{
		if (parser_arguments_to_program(program, argv) != OK)
			return (exit_status);
		if (init_program(program) != OK)
			return (exit_status);
		if (program->total_philos > 1)
		{
			if (start_program(program) != OK)
				return (exit_status);
		}
		else
			case_one_philo(program);
		if (free_program(program) != OK)
			return (exit_status);
		return (!exit_status);
	}
	return (free(program), ft_putendl_fd(MESSAGE_ERROR_INVALID_ARGUMENTS, 2) \
	, exit_status);
}

int	main(int argc, char **argv)
{
	t_program	*program;
	int			exit_status;

	exit_status = 1;
	program = get_malloc_memory(sizeof(t_program));
	if (!program)
		return (exit_status);
	return (wrapper_philosophers(argc, argv, program, exit_status));
}
