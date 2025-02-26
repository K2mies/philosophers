/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass_arguments_to_threads00.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:13:16 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/19 11:11:11 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int	primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void	*routine(void *arg)
{
	int index = *(int*)arg;
	printf("%d ", primes[index]);
	free(arg);
	return (0);
}

int	main(int argc, char **argv)
{
	pthread_t th[10];

	int i = -1;
	while (++i < 10)
	{
		int *a = malloc(sizeof(int));
		*a = i;
		if(pthread_create(&th[i], NULL, &routine, a) != 0)
		{
			perror("Failed to create thread\n");
		}
	}
	i = -1;
	while (++i < 10)
	{
		if(pthread_join(th[i], NULL) != 0)
		{
			perror("Failed to join thread\n");
		}
	}
	return (0);
}
