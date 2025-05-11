/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:16:06 by julcalde          #+#    #+#             */
/*   Updated: 2025/05/11 14:57:34 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(t_data *data, int argc, char **argv)
{
	data->num_philos = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->required_meals = ft_atoi(argv[5]);
	else
		data->required_meals = -1;
	if ((data->num_philos < 1 || data->num_philos > 200) || \
		(data->time_to_die < 60 || data->time_to_die > 2010) || \
		(data->time_to_eat < 60 || data->time_to_eat > 1000) || \
		(data->time_to_sleep < 60 || data->time_to_sleep > 1000))
	{
		printf(USAGE_MSG);
		exit(EXIT_FAILURE);
	}
	data->is_dead = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->forks)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	init_mutexes(data);
	data->start_time = get_time_msec();
}

int	ft_atoi(const char *str)
{
	int	i;
	int	result;

	result = 0;
	i = 0;
	while (str[i])
	{
		if (!str[i] || (str[i] < '0' || str[i] > '9'))
		{
			printf(USAGE_MSG);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	i = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		result *= 10;
		result += str[i] - 48;
		i++;
	}
	return (result);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}
