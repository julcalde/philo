/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:18:26 by julcalde          #+#    #+#             */
/*   Updated: 2025/05/06 21:23:20 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&data->print_mutex, NULL))
		return (-1);
	if (pthread_mutex_init(&data->dead_mutex, NULL))
	{
		pthread_mutex_destroy(&data->print_mutex);
		return (-1);
	}
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL))
		{
			while (--i)
				pthread_mutex_destroy(&data->forks[i]);
			return (-1);
		}
		i++;
	}
	return (0);
}

void	destroy_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->print_mutex);
	pthread_mutex_destroy(&data->dead_mutex);
}
