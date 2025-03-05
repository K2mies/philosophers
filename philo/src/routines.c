/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:31:35 by rhvidste          #+#    #+#             */
/*   Updated: 2025/03/05 15:28:41 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Function for THINKing routine.
int	think(t_philo *philo)
{
	print_message("is thinking", philo, philo->id);
	if (ft_usleep(1, philo) != 0)
		return (1);
	return (0);
}

// Function for SLEEPing routine
int	dream(t_philo *philo)
{
	print_message("is sleeping", philo, philo->id);
//	if (ft_usleep(1, philo) != 0)
	if (ft_usleep(philo->time_to_sleep, philo) != 0)
		return (1);
	return (0);
}

// Function for EATing routine.
int	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->r_fork->fork);
	philo->r_fork->lock = true;
	print_message("has taken a fork", philo, philo->id);
	if (philo->num_of_philos == 1)
	{
		ft_usleep(philo->time_to_die, philo);
		philo->r_fork->lock = false;
		pthread_mutex_unlock(&philo->r_fork->fork);
		return (1);
	}
	pthread_mutex_lock(&philo->l_fork->fork);
	philo->l_fork->lock = true;
	print_message("has taken a fork", philo, philo->id);
	print_message("is eating", philo, philo->id);
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	if (ft_usleep(philo->time_to_eat, philo) != 0)
	{
//		printf("ft usleep fail\n");
		philo->l_fork->lock = false;
		pthread_mutex_unlock(&philo->l_fork->fork);
		philo->r_fork->lock = false;
		pthread_mutex_unlock(&philo->r_fork->fork);
//		printf("Philo %d dropped his forks\n", philo->id);
		return 1;
	}
	pthread_mutex_lock(&philo->data->write_lock);
	philo->l_fork->lock = false;
	pthread_mutex_unlock(&philo->data->write_lock);
	pthread_mutex_unlock(&philo->l_fork->fork);
	pthread_mutex_lock(&philo->data->write_lock);
	philo->r_fork->lock = false;
	pthread_mutex_unlock(&philo->data->write_lock);
	pthread_mutex_unlock(&philo->r_fork->fork);
//	printf("Philo %d dropped his forks\n", philo->id);
	return (0);
}
