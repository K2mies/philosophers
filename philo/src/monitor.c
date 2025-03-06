/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:47:39 by rhvidste          #+#    #+#             */
/*   Updated: 2025/03/06 10:50:23 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Funtion to print message
void	print_message(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->dead_lock);
	time = get_current_time() - philo->start_time;
	if (!*philo->dead)
		printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->dead_lock);
}

// Function to check if specific philosopher is dead
int	philosopher_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_current_time() - philo->last_meal >= time_to_die)
	{
		pthread_mutex_unlock(philo->meal_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

// Function to check if any philosopher has died
int	check_if_dead(t_philo *philos)
{
	int		i;

	i = -1;
	while (++i < philos[0].num_of_philos)
	{
		if (philosopher_dead(&philos[i], philos[i].time_to_die))
		{
			pthread_mutex_lock(philos[0].dead_lock);
			print_death_message("died", &philos[i], philos[i].id);
			*philos->dead = true;
			pthread_mutex_unlock(philos[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

// Function to check if all the philos ate the number of meals
int	check_if_all_ate(t_philo *philos)
{
	int	i;
	int	finished_eating;

	i = -1;
	finished_eating = 0;
	if (philos[0].num_times_to_eat == -1)
		return (0);
	while (++i < philos[0].num_of_philos)
	{
		pthread_mutex_lock(philos[i].meal_lock);
		if (philos[i].meals_eaten >= philos[i].num_times_to_eat)
			finished_eating++;
		pthread_mutex_unlock(philos[i].meal_lock);
	}
	if (finished_eating == philos[0].num_of_philos)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->dead = true;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}

// Function to monitor routine
void	*monitor(void *pointer)
{
	t_philo	*philos;

	philos = (t_philo *)pointer;
	while (1)
		if (check_if_dead(philos) == 1 || check_if_all_ate(philos) == 1)
			break ;
	return (pointer);
}
