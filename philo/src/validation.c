/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rhvidste <rhvidste@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 15:56:12 by rhvidste          #+#    #+#             */
/*   Updated: 2025/03/06 10:47:06 by rhvidste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Function to check that argv inputs are valid
int	is_valid(int argc, char **argv)
{
	if (ft_atoi(argv[1]) <= 0 || is_valid_number(argv[1]) == 0)
		return (0);
	if (ft_atoi(argv[2]) <= 0 || is_valid_number(argv[2]) == 0)
		return (0);
	if (ft_atoi(argv[3]) <= 0 || is_valid_number(argv[3]) == 0)
		return (0);
	if (ft_atoi(argv[4]) <= 0 || is_valid_number(argv[4]) == 0)
		return (0);
	if (argc == 6 && (ft_atoi(argv[5]) <= 0 || is_valid_number(argv[5]) == 0))
		return (0);
	return (1);
}

// Function to check if argv contains non numeric characters
int	is_valid_number(char *arg)
{
	int		i;

	i = -1;
	while (arg[++i])
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (0);
	}
	return (1);
}
