/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:10:25 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/21 16:43:50 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//int	thread_create(t_data *data)
//{
//	int	i;
//
//	if (pthread_create(&data->observer, NULL, &monitor, data->philos) != 0)
//		destroy_all(&data);
//
//	i = -1;
//
//
//}

int	main(int argc, char **argv)
{
	t_data	data;
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

	//init data/program
	init_data(&data, argv);
	//init_forks
	init_forks(&data, argv);
	//init_philos
	init_philos(&data, argv);
	//thread_create

	//destroy_all
	destroy_all(&data);
	printf("data dead flag: %s\n", data.dead_flag ? "true" : "false");
	printf("program executed\n");
	int	i;
	i = -1;
	while (++i < data.philos[0].num_of_philos)
	{
		printf("philo %d, start_time: %zu , dead = %s\n", i, data.philos[i].start_time, *data.philos[i].dead ? "true" : "false");
	}

	data.dead_flag = true;
	printf("data dead flag: %s\n", data.dead_flag ? "true" : "false");
	printf("after change of data flag: dead philo = %s\n", *data.philos[0].dead ? "true" : "false");
//	printf("start_time: %zu\n", data.philos[0].start_time);
//	printf("start_time: %zu\n", data.philos[1].start_time);
//	printf("start_time: %zu\n", data.philos[2].start_time);
	//free all
	free_all(&data);
	return (0);
}
