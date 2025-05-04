/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:25:27 by julcalde          #+#    #+#             */
/*   Updated: 2025/05/04 14:37:58 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	take_forks(t_philo *philo)
// {
// 	t_data	*data;
// 	int		left;
// 	int		right;

// 	data = philo->data;
// 	left = philo->id;
// 	right = (philo->id + 1) % data->num_philos;
// 	if (data->num_philos == 1)
// 	{
// 		pthread_mutex_lock(&data->forks[left]);
// 		print_status(philo, "has taken a fork");
// 		return ;
// 	}
// 	if (philo->id % 2 == 0)
// 	{
// 		pthread_mutex_lock(&data->forks[right]);
// 		print_status(philo, "has taken a fork");
// 		if (pthread_mutex_trylock(&data->forks[left]) != 0)
// 		{
// 			pthread_mutex_unlock(&data->forks[right]);
// 			ft_usleep(10, philo);
// 			return (take_forks(philo));
// 		}
// 	}
// 	else
// 	{
// 		pthread_mutex_lock(&data->forks[left]);
// 		print_status(philo, "has taken a fork");
// 		if (pthread_mutex_trylock(&data->forks[right]) != 0)
// 		{
// 			pthread_mutex_unlock(&data->forks[left]);
// 			ft_usleep(10, philo);
// 			return (take_forks(philo));
// 		}
// 	}
// 	print_status(philo, "has taken a fork");
// }

static int	take_first_fork(t_philo *philo, int *first, int *second)
{
	t_data	*data;

	data = philo->data;
	*first = philo->id;
	*second = (philo->id + 1) % data->num_philos;
	if (data->num_philos == 1)
	{
		pthread_mutex_lock(&data->forks[*first]);
		return (print_status(philo, "has taken a fork"), 1);
	}
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&data->forks[*second]);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&data->forks[*first]);
		print_status(philo, "has taken a fork");
	}
	return (0);
}

static int	take_second_fork(t_philo *philo, int first, int second)
{
	t_data	*data;

	data = philo->data;
	if (philo->id % 2 == 0)
	{
		if (pthread_mutex_trylock(&data->forks[first]))
		{
			pthread_mutex_unlock(&data->forks[second]);
			return (ft_usleep(10, philo), 1);
		}
	}
	else
	{
		if (pthread_mutex_trylock(&data->forks[second]))
		{
			pthread_mutex_unlock(&data->forks[first]);
			return (ft_usleep(10, philo), 1);
		}
	}
	print_status(philo, "has taken a fork");
	return (0);
}

void	take_forks(t_philo *philo)
{
	int	first;
	int	second;

	if (take_first_fork(philo, &first, &second))
		return ;
	if (take_second_fork(philo, first, second))
		return (take_forks(philo));
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
