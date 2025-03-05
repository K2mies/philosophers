/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:19:07 by rhvidste          #+#    #+#             */
/*   Updated: 2025/03/05 15:57:45 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Function to check if the value of dead_flag has changed
int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

//can probibly remove this but try disabling it first
//int	sim_started(t_philo *philo)
//{
//	bool	val;
//	pthread_mutex_lock(&philo->data->write_lock);
//	val = philo->data->ready;
////	printf(" val is %s\n", val ? "true" : "false");
//	pthread_mutex_unlock(&philo->data->write_lock);
//	return (val);
//}

// Function for philosopher routine/thread
void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
//	while(!sim_started(philo))
//	{
//		ft_usleep(300, philo);
//	}
//	printf("sim started\n");
	pthread_mutex_lock(&philo->data->write_lock);
	if (philo->data->error == true)
	{
//		printf("error is read as true\n");
		pthread_mutex_unlock(&philo->data->write_lock);
		return (NULL);
	}
//	philo->start_time = get_current_time();
//	printf("philo start time is %zu\n", philo->start_time);
	pthread_mutex_unlock(&philo->data->write_lock);
	if (philo->id % 2 == 0)
//		think(philo);
		ft_usleep(10, philo);
	while(!dead_loop(philo))
	{
		if (eat(philo) == 1)
			break ;
		if (dream(philo) == 1)
			break ;
		if (think(philo) == 1)
			break ;
	}
	return (pointer);
}

// Function to create and join threads
int	thread_create(t_data *data)
{
	int	i;

	if (pthread_create(&data->observer, NULL, &monitor, data->philos) != 0)
	{
		pthread_join(data->observer, NULL);
		return (1);
	}
	i = -1;
	while (++i < data->philos[0].num_of_philos)
	{
//		if (i == 8 || pthread_create(&data->philos[i].thread,
		if (pthread_create(&data->philos[i].thread,
				NULL, &philo_routine, &data->philos[i]) != 0)
		{
			pthread_mutex_lock(&data->write_lock);
//			data->ready = true;
			data->error = true;
			pthread_mutex_unlock(&data->write_lock);
			pthread_mutex_lock(&data->dead_lock);
//			printf("emergency\n");
			data->dead_flag = true;
			pthread_mutex_unlock(&data->dead_lock);
			while(i--)
			{	
				pthread_join(data->philos[i].thread, NULL);
				printf("joined thread %d\n", i);
			}
			pthread_join(data->observer, NULL);
			return (1);
		}
	}
	pthread_mutex_lock(&data->write_lock);
//	data->ready = true;
	pthread_mutex_unlock(&data->write_lock);
	i = -1;
	if (pthread_join(data->observer, NULL) != 0)
		return(1);
	while (++i < data->philos[0].num_of_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
		{
			return (1);
		}
	}
	return (0);
}
