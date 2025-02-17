/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreadloop00.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:52:21 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/17 17:12:56 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int	mails = 0;
//int	lock = 0;
pthread_mutex_t	mutex;

void	*routine()
{
	int	i;
	i = -1;
	while (++i < 100000)//creates a race condition
	{
//		if (lock == 1)
//		{
//			//wait untill the lock is 0
//		}
//		lock = 1;
		pthread_mutex_lock(&mutex); //lock == 1 (locked)
		mails++;
		pthread_mutex_unlock(&mutex); //lock == 0 (unlocked)
//		lock = 0;
		// read mails
		// incrament
		// write mails
	}
	return (0);
}

int	main(int argc, char **argv)
{
	pthread_t th[8];
	int	i = -1;
	pthread_mutex_init(&mutex, NULL);
	while (++i < 8)
	{
		if (pthread_create(&th[i], NULL, &routine, NULL) != 0)
		{
			perror("Failed to create thread");
			return (1);
		}
		printf("Thread %d has started\n", i);
	}
	i = -1;
	while (++i < 8)
	{
		if (pthread_join(th[i], NULL) != 0)
		{
			return (2);
		}
		printf("Thread %d has finished execution\n", i);	
	}
	pthread_mutex_destroy(&mutex);
	printf("number of mails: %d\n", mails);
	return (0);
}

