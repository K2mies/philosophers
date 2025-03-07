/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:07:53 by rhvidste          #+#    #+#             */
/*   Updated: 2025/03/07 11:56:56 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	long	res;
	int		sign;

	res = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		if (res < 0 && sign > 0)
			return ((int)LONG_MAX);
		if (res < 0 && sign < 0)
			return ((int)LONG_MIN);
		str++;
	}
	return (res * sign);
}

//Improved version of sleep function
int	ft_usleep(size_t milliseconds, t_philo *philo)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start < milliseconds))
	{
		usleep(500);
		if (simulation_ended(philo->data) == 1)
		{
			return (1);
		}
	}
	return (0);
}

// Function to get current time in milliseconds
size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("gettimeofday() error\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

// Function to get int max
int	max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

// Function to get int min
int	min(int a, int b)
{
	if (a < b)
		return (a);
	else
		return (b);
}
