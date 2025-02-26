/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:28:30 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/26 13:49:14 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>
# include <math.h>

//# define PHILO_MAX 200

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	bool				eating;
	int					meals_eaten;
	size_t				last_meal;
	size_t				time_to_die;
	size_t				time_to_eat;
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

typedef struct s_data
{
	pthread_t			observer;
	bool				dead_flag;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		write_lock;
	t_philo				*philos;
	pthread_mutex_t		*forks;
}						t_data;

//Utils-------------------------------------------------------------------------
int		ft_atoi(const char *str);
int		ft_usleep(size_t milliseconds);
size_t	get_current_time(void);
//Validation--------------------------------------------------------------------
int		is_valid(int argc, char **argv);
int		is_valid_number(char *arg);
// Error------------------------------------------------------------------------
void	destroy_and_free_all(t_data *data);
void	free_all(t_data *data);
void	destroy_all(t_data *data);
//INIT--------------------------------------------------------------------------
void	init_data(t_data *data, char **argv);
void	init_input(t_philo *philo, char **argv);
void	init_philos(t_data *data, char **argv);
void	init_forks(t_data *data, char **argv);
//Threads----------------------------------------------------------------------
int		thread_create(t_data *data);
void	*philo_routine(void *pointer);
int		dead_loop(t_philo *philo);
//Routines--------------------------------------------------------------------
void	think(t_philo *philo);
void	dream(t_philo *philo);
void	eat(t_philo *philo);
//Monitor---------------------------------------------------------------------
void	print_message(char *str, t_philo *philo, int id);
int		philosopher_dead(t_philo *philo, size_t time_to_die);
int		check_if_dead(t_philo *philos);
int		check_if_all_ate(t_philo *philos);
void	*monitor(void *pointer);
#endif
