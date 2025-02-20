/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:28:30 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/20 13:54:16 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <math.h>

typedef struct			s_philo
{
	pthread_t			thread;
	int					id;
	bool				eating;
	int					meals_eaten;
	size_t				last_meal;
	size_t				time_to_die;
	size_t				time_to_sleep;
	size_t				start_time;
	int					num_of_philos;
	int					num_times_to_eat;
	bool				*dead;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*write_lock;
	pthread_mutex_t		*dead_lock;
	pthread_mutex_t		*meal_lock;
}						t_philo;

typedef struct			s_program
{
	bool				dead_flag;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		write_lock;
	t_philo				*philos;
}						t_program;

#endif
