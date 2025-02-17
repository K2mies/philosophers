/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   racecondition00.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:52:21 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/17 15:29:52 by rhvidste         ###   ########.fr       */
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
	pthread_t p1, p2, p3, p4;
	pthread_mutex_init(&mutex, NULL);
	if (pthread_create(&p1, NULL, &routine, NULL) != 0)
	{
		return (1);
	}
	if (pthread_create(&p2, NULL, &routine, NULL) != 0)
	{
		return (2);
	}
	if (pthread_create(&p3, NULL, &routine, NULL) != 0)
	{
		return (3);
	}
	if (pthread_create(&p4, NULL, &routine, NULL) != 0)
	{
		return (4);
	}
	if (pthread_join(p1, NULL) != 0)
	{
		return (5);
	}
	if (pthread_join(p2, NULL) != 0)
	{
		return (6);
	}
	if (pthread_join(p3, NULL) != 0)
	{
		return (7);
	}
	if (pthread_join(p4, NULL) != 0)
	{
		return (8);
	}
	pthread_mutex_destroy(&mutex);
	printf("number of mails: %d\n", mails);
	return (0);
}

