/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trylock_lock_example00.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:53:37 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/19 13:06:07 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t	mutex;

void	*routine(void *arg)
{
	if(pthread_mutex_trylock(&mutex) == 0)
	{	
		printf("got lock\n");
		usleep(1000000);
		pthread_mutex_unlock(&mutex);
	}
	else 
	{
		printf("didn't get lock\n");
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	pthread_t	*th;
	th = malloc(sizeof(pthread_t) * 4);

	pthread_mutex_init(&mutex, NULL);
	int i = -1;
	while (++i < 4)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
		{
			perror("Error createing thread\n");
		}
	}
	i = -1;
	while (++i < 4)
	{
		if (pthread_join(th[i], NULL) != 0)
		{
			perror("Error joining thread\n");
		}
	}
	pthread_mutex_destroy(&mutex);
	return (0);
}
