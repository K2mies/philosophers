/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   summing_numbers_from_array00.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:13:16 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/19 11:53:19 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int	primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void	*routine(void *arg)
{
//	useconds_t	usecs;
//	usecs = 5000000;
//	if(usleep(usecs) != 0)
//	{
//		perror("usleep failed\n");
//	}
	int index = *(int*)arg;
	int	sum = 0;
	int	i = -1;
	while (++i < 5)
	{
		sum += primes[index + i];
	}
	printf("Local sum: %d\n", sum);
	*(int*)arg = sum;
	return (arg);
}

int	main(int argc, char **argv)
{
	pthread_t th[2];

	int i = -1;
	while (++i < 2)
	{
		int *a = malloc(sizeof(int));
		*a = i * 5;
		if(pthread_create(&th[i], NULL, &routine, a) != 0)
		{
			perror("Failed to create thread\n");
		}
	}
	int	globalSum = 0;
	i = -1;
	while (++i < 2)
	{
		int *r;
		if(pthread_join(th[i], (void **)&r) != 0)
		{
			perror("Failed to join thread\n");
		}
		globalSum += *r;
		free(r);
	}
	printf("Global sum: %d\n", globalSum);
	return (0);
}
