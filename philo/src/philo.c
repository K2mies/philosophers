/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:10:25 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/24 16:19:19 by rhvidste         ###   ########.fr       */
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
	printf("program executed\n");
	thread_create(&data);
	//destroy_all
	destroy_all(&data);

	//TESTING---------------------------------------------------------
//	printf("data dead flag: %s\n", data.dead_flag ? "true" : "false");
//	printf("program executed\n");
//	int	i;
//	i = -1;
//	while (++i < data.philos[0].num_of_philos)
//	{
//		printf("philo %d, start_time: %zu , dead = %s\n", i, data.philos[i].start_time, *data.philos[i].dead ? "true" : "false");
//	}
//	data.dead_flag = true;
	// the philo and data dead flags are pointers so if you update the dereference of one it will update for the others.
	// to check the flag you also have to dereference otherwise it will evaluate the pointer rather thatn the true/false value.
//	printf("data dead flag: %s\n", data.dead_flag ? "true" : "false");
//	printf("after change of data flag: dead philo = %s\n", *data.philos[0].dead ? "true" : "false");
	//free all
	free_all(&data);
	return (0);
}
