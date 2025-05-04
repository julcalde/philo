/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 19:52:36 by julcalde          #+#    #+#             */
/*   Updated: 2025/05/04 19:52:42 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	acquire_even_first(t_philo *philo, int *first, int *second)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->forks[*second]);
	print_status(philo, "has taken a fork");
	if (pthread_mutex_trylock(&data->forks[*first]))
	{
		pthread_mutex_unlock(&data->forks[*second]);
		if (check_death(philo))
			return (0);
		ft_usleep(10, philo);
		return (1);
	}
	return (0);
}

int	acquire_odd_first(t_philo *philo, int *first, int *second)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->forks[*first]);
	print_status(philo, "has taken a fork");
	if (pthread_mutex_trylock(&data->forks[*second]))
	{
		pthread_mutex_unlock(&data->forks[*first]);
		if (check_death(philo))
			return (0);
		ft_usleep(10, philo);
		return (1);
	}
	return (0);
}

int	acquire_even_second(t_philo *philo, int first, int second)
{
	t_data	*data;

	data = philo->data;
	if (pthread_mutex_trylock(&data->forks[first]))
	{
		pthread_mutex_unlock(&data->forks[second]);
		if (check_death(philo))
			return (0);
		ft_usleep(10, philo);
		return (1);
	}
	return (0);
}

int	acquire_odd_second(t_philo *philo, int first, int second)
{
	t_data	*data;

	data = philo->data;
	if (pthread_mutex_trylock(&data->forks[second]))
	{
		pthread_mutex_unlock(&data->forks[first]);
		if (check_death(philo))
			return (0);
		ft_usleep(10, philo);
		return (1);
	}
	return (0);
}
