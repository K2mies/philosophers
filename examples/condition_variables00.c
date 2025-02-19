/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   condition_variables00.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:14:28 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/19 15:05:26 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

pthread_mutex_t	mutexFuel;
pthread_cond_t	condFuel;
int	fuel = 0;

void	*fuel_filling(void *arg)
{
	int	i = -1;
	while (++i < 5)
	{
		pthread_mutex_lock(&mutexFuel);
		fuel += 15;
		printf("Filled fuel... %d\n", fuel);
		pthread_mutex_unlock(&mutexFuel);
		pthread_cond_signal(&condFuel);
		usleep(1000000);
	}
	return (NULL);
//	printf("Filling fuel\n");
}

void	*car(void *arg)
{
	pthread_mutex_lock(&mutexFuel);
	while (fuel < 40)
	{
		printf("no fuel. Waiting...\n");
		pthread_cond_wait(&condFuel, &mutexFuel);
	}
	fuel -= 40;
	printf("got fuel. Now left: %d\n", fuel);
	pthread_mutex_unlock(&mutexFuel);
//	printf("Here to get fuel\n");
	return (NULL);
}

int	main(int argc, char **argv)
{
	pthread_t	*th;
	th = malloc(sizeof(pthread_t) * 2);
	if (th == NULL)
	{
		perror("malloc failed");
	}
	pthread_mutex_init(&mutexFuel, NULL);
	pthread_cond_init(&condFuel, NULL);
	int	i =-1;
	while(++i < 2)
	{
		if (i == 1)
		{
			if (pthread_create(&th[i], NULL, &fuel_filling, NULL) != 0)
			{
				perror("Failed to create thread\n");
			}
		}
		else
		{
			if (pthread_create(&th[i], NULL, &car, NULL) != 0)
			{
				perror("Failed to create thread\n");
			}
		}
	}

	i = -1;
	while (++i < 2)
	{
		if (pthread_join(th[i], NULL) != 0)
		{
			perror("Failed to join thread\n");
		}
	}
	pthread_mutex_destroy(&mutexFuel);
	pthread_cond_destroy(&condFuel);
	return (0);
}
