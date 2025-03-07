/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:10:25 by rhvidste          #+#    #+#             */
/*   Updated: 2025/03/07 11:13:52 by rhvidste         ###   ########.fr       */
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
	if (init_data(&data, argv) == 1)
		return (1);
	if (init_forks(&data, argv) == 1)
		return (1);
	init_philos(&data, argv);
	thread_create(&data);
	destroy_all(&data);
	free_all(&data);
	return (0);
}
