/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads01.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:19:46 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/17 13:53:23 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

//You need to add the "-pthread" flag to your compile ie:
//gcc -pthread threads01.c

void	*routine() 
{
	printf("test from threads\n");
	sleep(3);
	printf("Ending thread\n");
	return (0);
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	pthread_t	t1, t2;
	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
	{
		return (1);
	}
	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
	{
		return (2);
	}
	// Same as wait()
	if (pthread_join(t1, NULL) != 0)
	{
		return (3);
	}
	if(pthread_join(t2, NULL) != 0)
	{
		return (4);
	}
	return (0);
}
