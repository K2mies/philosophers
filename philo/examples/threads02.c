/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads02.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 13:40:32 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/17 13:53:45 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int x = 2;

//gcc -pthread threads02.c
void	*routine()
{
	x++;
	sleep(2);
	printf("Value of x: %d\n", x);
//	printf("process id %d\n", getpid());
	return (0);
}

void	*routine2()
{
	// you can see here that the routines share memory (x);
	sleep(2);
	printf("Value of x: %d\n", x);
//	printf("process id %d\n", getpid());
	return (0);
}

int	main(int argc, char **argv)
{
	pthread_t t1, t2;
	if (pthread_create(&t1, NULL, &routine, NULL))
	{
		return (1);
	}
	if (pthread_create(&t2, NULL, &routine2, NULL))
	{
		return (2);
	}
	if (pthread_join(t1, NULL))
	{
		return (3);
	}
	if (pthread_join(t2, NULL))
	{
		return (3);
	}
	return (0);
}
