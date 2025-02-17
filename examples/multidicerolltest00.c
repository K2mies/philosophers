/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multidicerolltest00.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:23:17 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/17 17:13:00 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

pthread_mutex_t mutex;

void	*roll_dice()
{
	pthread_mutex_lock(&mutex);
	int	value = (rand() %6) + 1;
	int	*result = malloc(sizeof(int));
	*result = value;
	pthread_mutex_unlock(&mutex);
	return ((void *) result);
}

int	main(int argc, char **argv)
{
	int	*res;
	srand(time(NULL));
//	pthread_mutex_t	mutex;
	pthread_t	th[8];
	int	i = -1;
	pthread_mutex_init(&mutex, NULL);
	while (++i < 8)
	{
		if (pthread_create(&th[i], NULL, &roll_dice, NULL) != 0)
		{
			perror("Failed to create thread");
			return (1);
		}
		printf("Thread %d has started\n", i);
	}
	i = -1;
	while (++i < 8)
	{
		if (pthread_join(th[i], (void**) &res))
		{
			return (2);
		}
		printf("result: %d\n", *res);
		free(res);
		printf("Thread %d has finished execution\n", i);
	}
	pthread_mutex_destroy(&mutex);
}
