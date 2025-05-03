/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:18:26 by julcalde          #+#    #+#             */
/*   Updated: 2025/05/03 20:50:17 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print_mutex, NULL);
	pthread_mutex_init(&data->dead_mutex, NULL);
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

void	take_forks(t_philo *philo)
{
	t_data	*data;
	int		left;
	int		right;

	data = philo->data;
	left = philo->id;
	right = (philo->id + 1) % data->num_philos;
	if (data->num_philos == 1)
	{
		pthread_mutex_lock(&data->forks[left]);
		print_status(philo, "has taken a fork");
		return ;
	}
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&data->forks[right]);
		print_status(philo, "has taken a fork");
		if (pthread_mutex_trylock(&data->forks[left]) != 0)
		{
			pthread_mutex_unlock(&data->forks[right]);
			ft_usleep(10, philo);
			return (take_forks(philo));
		}
	}
	else
	{
		pthread_mutex_lock(&data->forks[left]);
		print_status(philo, "has taken a fork");
		if (pthread_mutex_trylock(&data->forks[right]) != 0)
		{
			pthread_mutex_unlock(&data->forks[left]);
			ft_usleep(10, philo);
			return (take_forks(philo));
		}
	}
	print_status(philo, "has taken a fork");
}

void	release_forks(t_philo *philo)
{
	t_data	*data;
	int		left;
	int		right;

	data = philo->data;
	left = philo->id;
	right = (philo->id + 1) % data->num_philos;
	if (data->num_philos == 1)
		pthread_mutex_unlock(&data->forks[left]);
	else
	{
		pthread_mutex_unlock(&data->forks[left]);
		pthread_mutex_unlock(&data->forks[right]);
	}
}
