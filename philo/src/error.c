/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:15:13 by rhvidste          #+#    #+#             */
/*   Updated: 2025/03/05 17:08:19 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//Function to print death message
void	print_death_message(char *str, t_philo *philo, int id)
{
	size_t	time;

//	pthread_mutex_lock(philo->dead_lock);
	time = get_current_time() - philo->start_time;
//	if (*philo->dead)
	printf("%zu %d %s\n", time, id, str);
//	pthread_mutex_unlock(philo->dead_lock);
}

//Function to check if simulation has ended
int	simulation_ended(t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	if (data->dead_flag == true)
	{		
		pthread_mutex_unlock(&data->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->dead_lock);
	return (0);
}

//Function to destory and free all.
void	destroy_and_free_all(t_data *data)
{
	destroy_all(data);
	free_all(data);
}

// Functiont to clean up data
void	free_all(t_data *data)
{
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
}

// Function to destroy all mutex
void	destroy_all(t_data *data)
{
	int	i;

//	pthread_mutex_unlock(&data->write_lock);
//	pthread_mutex_unlock(&data->meal_lock);
//	if (pthread_mutex_unlock(&data->write_lock))
//		print_message("error mutex writelock\n", &data->philos[0], 0);
//	if (pthread_mutex_unlock(&data->meal_lock))
//		print_message("error mutex meallock\n", &data->philos[0], 0);
//	if (pthread_mutex_unlock(&data->dead_lock) == 0)
//		printf("testing sdklfjslk\n");
//		print_message("error mutex deadlock\n", &data->philos[0], 0);

	pthread_mutex_lock(&data->dead_lock);
	i = -1;
	while (++i < data->philos[0].num_of_philos)
	{
		if (data->forks[i].lock == true)
		{
			pthread_mutex_unlock(&data->forks[i].fork);
			data->forks[i].lock = false;
		}
	}
	pthread_mutex_unlock(&data->dead_lock);

	pthread_mutex_destroy(&data->write_lock);
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->dead_lock);
	i = -1;
	while (++i < data->philos[0].num_of_philos)
		pthread_mutex_destroy(&data->forks[i].fork);
}
