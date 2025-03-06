/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:10:25 by rhvidste          #+#    #+#             */
/*   Updated: 2025/03/06 10:50:34 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 5 && argc != 6)
	{
		printf("wrong argument count\n");
		return (0);
	}
	if (is_valid(argc, argv) == 0)
	{
		printf("invalid input\n");
		return (0);
	}
	init_data(&data, argv);
	init_forks(&data, argv);
	init_philos(&data, argv);
	thread_create(&data);
	destroy_all(&data);
	free_all(&data);
	return (0);
}
