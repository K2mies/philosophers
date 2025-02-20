/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:10:25 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/20 17:02:54 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
//	(void)argc;
//	(void)argv;

	//VALIDATION CHECK-----------------------------
	if (argc != 5 && argc != 6)
	{
		printf("wrong argument count\n");
		exit(EXIT_FAILURE);
	}
	if (is_valid(argc, argv) == 0)
	{
		printf("invalid input\n");
		exit(EXIT_FAILURE);
	}
	//SUDO----------------------------------------
	
	//lets get the input variables.
	//number of philosophers
	//time to die
	//time to eat
	//time to sleep
	//number of times each philosopher must eat

	//init program
	//init_forks
	//init_philos
	//thread_create
	//destroy_all
	printf("program executed\n");
	return (0);
}
