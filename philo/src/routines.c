/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 15:31:35 by rhvidste          #+#    #+#             */
/*   Updated: 2025/03/07 11:44:59 by rhvidste         ###   ########.fr       */
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
	if (ft_usleep(philo->time_to_sleep, philo) != 0)
		return (1);
	return (0);
}

//EAT Helper function for one philo case
static int	one_philo(t_philo *philo)
{
	if (philo->num_of_philos == 1)
	{
		ft_usleep(philo->time_to_die, philo);
		philo->r_fork->lock = false;
		pthread_mutex_unlock(&philo->r_fork->fork);
		return (1);
	}
	return (0);
}

//EAT Helper function to put down forks and unlock them if dead.
static int	if_dead(t_philo *philo)
{
	if (ft_usleep(philo->time_to_eat, philo) != 0)
	{
		philo->l_fork->lock = false;
		pthread_mutex_unlock(&philo->l_fork->fork);
		philo->r_fork->lock = false;
		pthread_mutex_unlock(&philo->r_fork->fork);
		return (1);
	}
	return (0);
}

// Function for EATing routine.
int	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->r_fork->fork);
	philo->r_fork->lock = true;
	print_message("has taken a fork", philo, philo->id);
	if (one_philo(philo) == 1)
		return (1);
	pthread_mutex_lock(&philo->l_fork->fork);
	philo->l_fork->lock = true;
	print_message("has taken a fork", philo, philo->id);
	print_message("is eating", philo, philo->id);
	pthread_mutex_lock(philo->dead_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->dead_lock);
	if (if_dead(philo) == 1)
		return (1);
	pthread_mutex_lock(&philo->data->dead_lock);
	philo->l_fork->lock = false;
	pthread_mutex_unlock(&philo->data->dead_lock);
	pthread_mutex_unlock(&philo->l_fork->fork);
	pthread_mutex_lock(&philo->data->dead_lock);
	philo->r_fork->lock = false;
	pthread_mutex_unlock(&philo->data->dead_lock);
	pthread_mutex_unlock(&philo->r_fork->fork);
	return (0);
}
