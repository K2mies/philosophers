/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:10:25 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/27 17:07:35 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

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
	init_data(&data, argv);
	init_forks(&data, argv);
	init_philos(&data, argv);
	thread_create(&data);
	destroy_all(&data);
	free_all(&data);
	return (0);
}
