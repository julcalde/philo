/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:25:27 by julcalde          #+#    #+#             */
/*   Updated: 2025/05/04 20:49:43 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philo *philo)
{
	int	first;
	int	second;

	if (take_first_fork(philo, &first, &second))
		return ;
	if (take_second_fork(philo, first, second))
		return ;
	print_status(philo, "has taken a fork");
}

int	take_first_fork(t_philo *philo, int *first, int *second)
{
	t_data	*data;

	data = philo->data;
	*first = philo->id;
	*second = (philo->id + 1) % data->num_philos;
	if (data->num_philos == 1)
	{
		// if (check_death(philo))
		// 	return (1);
		pthread_mutex_lock(&data->forks[*first]);
		print_status(philo, "has taken a fork");
		return (1);
	}
	if (philo->id % 2 == 0)
	{
		if (acquire_even_first(philo, first, second))
			return (0);
	}
	else
	{
		if (acquire_odd_first(philo, first, second))
			return (0);
	}
	return (0);
}

int	take_second_fork(t_philo *philo, int first, int second)
{
	if (philo->id % 2 == 0)
	{
		acquire_even_second(philo, first, second);
	}
	else
	{
		acquire_odd_second(philo, first, second);
	}
	print_status(philo, "has taken a fork");
	return (0);
}

void	release_forks(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->num_philos == 1)
	{
		pthread_mutex_unlock(&data->forks[philo->id]);
		return ;
	}
	else
	{
		pthread_mutex_unlock(&data->forks[philo->id]);
		pthread_mutex_unlock(&data->forks[(philo->id + 1) % data->num_philos]);
	}
}
