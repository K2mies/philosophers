/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 11:19:07 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/27 17:07:28 by rhvidste         ###   ########.fr       */
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

// Function for philosopher routine/thread
void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		ft_usleep(10);
	while (!dead_loop(philo))
	{
		eat(philo);
		dream(philo);
		think(philo);
	}
	return (pointer);
}

// Function to create and join threads
int	thread_create(t_data *data)
{
	int	i;

	if (pthread_create(&data->observer, NULL, &monitor, data->philos) != 0)
		destroy_and_free_all(data);
	i = -1;
	while (++i < data->philos[0].num_of_philos)
	{
		if (pthread_create(&data->philos[i].thread,
				NULL, &philo_routine, &data->philos[i]) != 0)
		{
			destroy_and_free_all(data);
		}
	}
	i = -1;
	if (pthread_join(data->observer, NULL) != 0)
		destroy_and_free_all(data);
	while (++i < data->philos[0].num_of_philos)
	{
		if (pthread_join(data->philos[i].thread, NULL) != 0)
			destroy_and_free_all(data);
	}
	return (0);
}
