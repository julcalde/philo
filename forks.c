/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:25:27 by julcalde          #+#    #+#             */
/*   Updated: 2025/05/10 21:51:58 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		pthread_mutex_lock(&philo->data->forks[right]);
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[left]);
		print_status(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->data->forks[left]); // deadlock occurs here for test case "4 310 200 100"
		print_status(philo, "has taken a fork");
		pthread_mutex_lock(&philo->data->forks[right]);
		print_status(philo, "has taken a fork");
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
