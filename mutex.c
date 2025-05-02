/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:18:26 by julcalde          #+#    #+#             */
/*   Updated: 2025/05/02 15:03:24 by julcalde         ###   ########.fr       */
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
		print_status(philo, "has taken a L fork");
		return ;
	}
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&data->forks[right]);
		print_status(philo, "has taken a R1 fork");
		if (check_death(philo))
		{
			pthread_mutex_unlock(&data->forks[right]);
			print_status(philo, "has dropped a R1 fork");
			return ;
		}
		pthread_mutex_lock(&data->forks[left]);
		print_status(philo, "has found a L1 fork");
	}
	else
	{
		pthread_mutex_lock(&data->forks[left]);
		print_status(philo, "has taken a L2 fork");
		if (check_death(philo))
		{
			pthread_mutex_unlock(&data->forks[left]);
			print_status(philo, "has dropped a L2 fork");
			return ;
		}
		pthread_mutex_lock(&data->forks[right]);
		print_status(philo, "has found a R2 fork");
	}
	print_status(philo, "has taken a fork");
}

// Suggested alternative to the above function
void	take_forks(t_philo *philo)
{
	t_data	*data;
	int		left;
	int		right;

	data = philo->data;
	left = philo->id;
	right = (philo->id + 1) % data->num_philos;

	pthread_mutex_lock(&data->forks[left]);
	print_status(philo, "has taken a fork");
	if (get_is_dead(data))
	{
		pthread_mutex_unlock(&data->forks[left]);
		return ;
	}
	pthread_mutex_lock(&data->forks[right]);
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
	{
		pthread_mutex_unlock(&data->forks[left]);
		print_status(philo, "has released a L3 fork");
		return ;
	}
	pthread_mutex_unlock(&data->forks[left]);
	print_status(philo, "has released a L3 fork");
	pthread_mutex_unlock(&data->forks[right]);
	print_status(philo, "has released a R3 fork");
}

// // Suggested alternative to the above function
// void	release_forks(t_philo *philo)
// {
// 	t_data	*data;
// 	int		left;
// 	int		right;

// 	data = philo->data;
// 	left = philo->id;
// 	right = (philo->id + 1) % data->num_philos;

// 	pthread_mutex_unlock(&data->forks[left]);
// 	pthread_mutex_unlock(&data->forks[right]);
// }
