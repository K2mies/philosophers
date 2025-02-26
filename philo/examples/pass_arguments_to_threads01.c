/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pass_arguments_to_threads01.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 17:13:16 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/19 12:09:39 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

typedef struct s_data
{
	int			index;
	int			*primes;
	pthread_t	mutex;
}	t_data;

int	primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29};

void	*routine(void *arg)
{
	pthread_mutex_lock(&data->mutex);
	t_data	*data;
	data = (t_data *)arg;
	int index = malloc(sizeof(int));
	index = data->index;
	printf("%d ", index);
	pthread_mutex_unlock(&data->mutex);	
//	int index = *(int*)arg;
//	printf("%d ", primes[index]);
//	free(arg);
	return (0);
}

int main(int argc, char **argv)
{
    int primes[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    pthread_t *th = malloc(sizeof(pthread_t) * 10);
    t_data *data_array[10];

    for (int i = 0; i < 10; i++)
    {
        data_array[i] = malloc(sizeof(t_data));
        data_array[i]->index = i;
        data_array[i]->primes = primes;
        pthread_mutex_init(&data_array[i]->mutex, NULL);

        if (pthread_create(&th[i], NULL, &routine, data_array[i]) != 0)
        {
            perror("Failed to create thread\n");
        }
    }

    for (int i = 0; i < 10; i++)
    {
        if (pthread_join(th[i], NULL) != 0)
        {
            perror("Failed to join thread\n");
        }
        pthread_mutex_destroy(&data_array[i]->mutex);
        free(data_array[i]);
    }

    free(th);
    return 0;
}
