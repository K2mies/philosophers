/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_return_value00.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 16:02:38 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/19 10:50:22 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

void	*roll_dice()
{
	int value = (rand() % 6) + 1;
	int	*result = malloc(sizeof(int));
	*result = value;
//	printf("%d\n", value);
	printf("thread result: %p\n", result);
	return ((void *) result);
}

int	main(int argc, char **argv)
{
	int	*res;
	srand(time(NULL));
	pthread_t th;
	if (pthread_create(&th, NULL, &roll_dice, NULL) != 0)
	{
		return (1);
	}
	if (pthread_join(th, (void**) &res) != 0)
	{
		return (2);
	}
	printf("main result: %p\n", res);
	printf("Result: %d\n", *res);
	free(res);//remember to free memmory here.
	return (0);
}
