/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 19:52:36 by julcalde          #+#    #+#             */
/*   Updated: 2025/05/05 16:34:30 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	acquire_even_first(t_philo *philo, int *left, int *right)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->forks[*right]);
	print_status(philo, "has taken a fork");
	if (pthread_mutex_trylock(&data->forks[*left]))
	{
		pthread_mutex_unlock(&data->forks[*right]);
		ft_usleep(10, philo);
		if (check_death(philo))
			return (0);
		return (1);
	}
	return (0);
}

int	acquire_odd_first(t_philo *philo, int *left, int *right)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->forks[*left]);
	print_status(philo, "has taken a fork");
	if (pthread_mutex_trylock(&data->forks[*right]))
	{
		pthread_mutex_unlock(&data->forks[*left]);
		ft_usleep(10, philo);
		if (check_death(philo))
			return (0);
		return (1);
	}
	return (0);
}

int	acquire_even_second(t_philo *philo, int left, int right)
{
	t_data	*data;

	data = philo->data;
	if (pthread_mutex_trylock(&data->forks[left]))
	{
		pthread_mutex_unlock(&data->forks[right]);
		if (check_death(philo))
			return (0);
		ft_usleep(10, philo);
		return (1);
	}
	return (0);
}

int	acquire_odd_second(t_philo *philo, int left, int right)
{
	t_data	*data;

	data = philo->data;
	if (pthread_mutex_trylock(&data->forks[right]))
	{
		pthread_mutex_unlock(&data->forks[left]);
		if (check_death(philo))
			return (0);
		ft_usleep(10, philo);
		return (1);
	}
	return (0);
}
