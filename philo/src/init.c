/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:10:56 by rhvidste          #+#    #+#             */
/*   Updated: 2025/02/26 14:16:31 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Function to initialize data struct and malloc space
void	init_data(t_data *data, char **argv)
{
	int	count;

	count = ft_atoi(argv[1]);
	memset(data, 0, sizeof(t_data));
	data->dead_flag = false;
	data->philos = malloc(sizeof(t_philo) * count);
	if (data->philos == NULL)
		free_all(data);
	data->forks = malloc(sizeof(pthread_mutex_t) * count);
	if (data->forks == NULL)
		free_all(data);
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
	pthread_mutex_init(&data->write_lock, NULL);
}

// Function to initializ input from the user
void	init_input(t_philo *philo, char **argv)
{
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	philo->num_of_philos = ft_atoi(argv[1]);
	if (argv[5])
		philo->num_times_to_eat = ft_atoi(argv[5]);
	else
		philo->num_times_to_eat = -1;
}

// Function to initialize philosophers data

void	init_philos(t_data *d, char **argv)
{
	int		i;

	i = -1;
	while (++i < ft_atoi(argv[1]))
	{
		d->philos[i].id = i + 1;
		d->philos[i].eating = false;
		d->philos[i].meals_eaten = 0;
		init_input(&d->philos[i], argv);
		d->philos[i].start_time = get_current_time();
		d->philos[i].last_meal = get_current_time();
		d->philos[i].write_lock = &d->write_lock;
		d->philos[i].dead_lock = &d->dead_lock;
		d->philos[i].meal_lock = &d->meal_lock;
		d->philos[i].dead = &d->dead_flag;
		d->philos[i].l_fork = &d->forks[i];
		if (i == 0)
			d->philos[i].r_fork = &d->forks[d->philos[i].num_of_philos - 1];
		else
			d->philos[i].r_fork = &d->forks[i - 1];
	}
}

// Function to initalize forks (mutex).
void	init_forks(t_data *data, char **argv)
{
	int	i;

	i = -1;
	while (++i < ft_atoi(argv[1]))
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			printf("mutex initialisation failedi\n");
			while (i--)
			{
				pthread_mutex_destroy(&data->forks[i]);
				printf("mutex destroyed\n");
				free_all(data);
			}
		}
	}
}
