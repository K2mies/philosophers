/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass_arguments_to_threads02.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 10:36:10 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/19 11:06:03 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct s_data
{
	int			index;
	int			*primes;
	pthread_t	mutex;
}

v

int	main(int argc, char **argv)
{
	int	primes[10] = {2, 3, 5, 7, 11, 13, 17, 23, 29};
	pthread_t	*th = malloc(sizeof(pthread_t) * 10);
	t_data *data;
	data->primes = primes;
	pthread_mutex_init(&data->mutex, NULL);
	int	i = -1;
	while (++i < 10)
	{
		data->index = i;

		if (pthread_create(&th[i], NULL, &routine, data) != 0)
		{
			perror("Failed to create thread\n");
			return (1);
		}
	}
	i = -1;
	while (++i < 10)
	{
		if (pthread_join(th[i], NULL) != 0)
		{
			perror("Failed to join thread\n");
		} 
	}
	pthread_mutex_destroy(&data->mutex);
}
