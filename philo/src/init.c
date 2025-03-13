/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 13:10:56 by rhvidste          #+#    #+#             */
/*   Updated: 2025/03/07 11:57:02 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Function to initialize data struct and malloc space
int	init_data(t_data *data, char **argv)
{
	int	count;

	count = ft_atoi(argv[1]);
	memset(data, 0, sizeof(t_data));
	data->philos = malloc(sizeof(t_philo) * count);
	if (data->philos == NULL)
	{
		free_all(data);
		return (1);
	}
	memset(data->philos, 0, sizeof(t_philo) * count);
	data->forks = malloc(sizeof(t_fork) * count);
	if (data->forks == NULL)
	{
		free_all(data);
		return (1);
	}
	memset(data->forks, 0, sizeof(t_fork) * count);
	if (pthread_mutex_init(&data->dead_lock, NULL) != 0)
	{
		free_all(data);
		return (1);
	}
	return (0);
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
		d->philos[i].meals_eaten = 0;
		init_input(&d->philos[i], argv);
		d->philos[i].start_time = get_current_time();
		d->philos[i].last_meal = get_current_time();
		d->philos[i].dead_lock = &d->dead_lock;
		d->philos[i].dead = &d->dead_flag;
		d->philos[i].data = d;
		d->philos[i].l_fork = &d->forks[min(i, ((i + 1) % d->num_of_forks))];
		d->philos[i].r_fork = &d->forks[max(i, ((i + 1) % d->num_of_forks))];
	}
}

// Function to initalize forks (mutex).
int	init_forks(t_data *data, char **argv)
{
	int	i;

	i = -1;
	while (++i < ft_atoi(argv[1]))
	{
		if (pthread_mutex_init(&data->forks[i].fork, NULL) != 0)
		{
			printf("mutex initialisation failedi\n");
			while (i--)
			{
				pthread_mutex_destroy(&data->forks[i].fork);
				printf("mutex destroyed\n");
			}
			free_all(data);
			return (1);
		}
	}
	data->num_of_forks = ft_atoi(argv[1]);
	return (0);
}
