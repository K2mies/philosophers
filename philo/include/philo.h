/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 11:28:30 by rhvidste          #+#    #+#             */
/*   Updated: 2025/03/05 15:15:21 by rhvidste         ###   ########.fr       */
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



typedef struct s_data	t_data;

typedef struct	s_fork
{
	bool			lock;
	pthread_mutex_t	fork;
}					t_fork;

typedef struct s_philo
{
	pthread_t			thread;
	int					id;
	int					meals_eaten;
	size_t				last_meal;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	size_t				start_time;
	int					num_of_philos;
	int					num_times_to_eat;
	bool				*dead;
	t_data				*data;
	t_fork				*r_fork;
	t_fork				*l_fork;
	pthread_mutex_t		*write_lock;
	pthread_mutex_t		*dead_lock;
	pthread_mutex_t		*meal_lock;
}						t_philo;

typedef struct s_data
{
	pthread_t			observer;
	bool				dead_flag;
	bool				error;
//	bool				ready;
	pthread_mutex_t		dead_lock;
	pthread_mutex_t		meal_lock;
	pthread_mutex_t		write_lock;
	t_philo				*philos;
	t_fork				*forks;
//	pthread_mutex_t		*forks;
	int					num_of_forks;
}						t_data;

//Utils-------------------------------------------------------------------------
int		ft_atoi(const char *str);
int		ft_usleep(size_t milliseconds, t_philo *philo);
size_t	get_current_time(void);
int		max(int a, int b);
int		min(int a, int b);
//Validation--------------------------------------------------------------------
int		is_valid(int argc, char **argv);
int		is_valid_number(char *arg);
// Error------------------------------------------------------------------------
int		simulation_ended(t_data *data);
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
int		think(t_philo *philo);
int		dream(t_philo *philo);
int		eat(t_philo *philo);
//Monitor---------------------------------------------------------------------
void	print_message(char *str, t_philo *philo, int id);
int		philosopher_dead(t_philo *philo, size_t time_to_die);
int		check_if_dead(t_philo *philos);
int		check_if_all_ate(t_philo *philos);
void	*monitor(void *pointer);
#endif
