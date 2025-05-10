/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:25:27 by julcalde          #+#    #+#             */
/*   Updated: 2025/05/10 22:09:02 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	even_ph_id(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id;
	right = (philo->id + 1) % philo->data->num_philos;
	pthread_mutex_lock(&philo->data->forks[right]);
	if (get_is_dead(philo->data))
	{
		pthread_mutex_unlock(&philo->data->forks[right]);
		return ;
	}
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[left]);
	if (get_is_dead(philo->data))
	{
		pthread_mutex_unlock(&philo->data->forks[right]);
		pthread_mutex_unlock(&philo->data->forks[left]);
		return ;
	}
	print_status(philo, "has taken a fork");
}

void	odd_ph_id(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id;
	right = (philo->id + 1) % philo->data->num_philos;
	pthread_mutex_lock(&philo->data->forks[left]); // here is the deadlock
	if (get_is_dead(philo->data))
	{
		pthread_mutex_unlock(&philo->data->forks[left]);
		return ;
	}
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[right]);
	if (get_is_dead(philo->data))
	{
		pthread_mutex_unlock(&philo->data->forks[left]);
		pthread_mutex_unlock(&philo->data->forks[right]);
		return ;
	}
	print_status(philo, "has taken a fork");
}

void	take_forks(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id;
	right = (philo->id + 1) % philo->data->num_philos;
	if (check_death(philo))
		return ;
	if (philo->id % 2 == 0)
	{
		even_ph_id(philo);
	}
	else
	{
		odd_ph_id(philo);
	}
	if (check_death(philo))
	{
		return ;
	}
}

void	release_forks(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id;
	right = (philo->id + 1) % philo->data->num_philos;

	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->data->forks[right]);
		pthread_mutex_unlock(&philo->data->forks[left]);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->forks[left]);
		pthread_mutex_unlock(&philo->data->forks[right]);
	}
}
