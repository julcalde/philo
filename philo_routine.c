/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:30:12 by julcalde          #+#    #+#             */
/*   Updated: 2025/05/10 21:41:26 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	philo->last_meal_time = data->start_time;
	if (philo->data->num_philos == 1)
	{
		loner_goner(philo);
		return (NULL);
	}
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!get_is_dead(data))
	{
		if (data->required_meals != -1 && \
			philo->meals_eaten >= data->required_meals)
			break ;
		if (!perform_cycle(philo))
		{
			break ;
		}
	}
	return (NULL);
}

int	perform_cycle(t_philo *philo)
{
	if (get_is_dead(philo->data))
		return (0);
	routine_eat(philo); //
	if (get_is_dead(philo->data))
		return (0);
	routine_sleep(philo);
	if (get_is_dead(philo->data))
		return (0);
	routine_think(philo);
	if (get_is_dead(philo->data))
		return (0);
	return (1);
}

void	loner_goner(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	pthread_mutex_lock(&data->forks[philo->id]);
	print_status(philo, "has taken a fork");
	ft_usleep(data->time_to_die, philo);
	check_death(philo);
	pthread_mutex_unlock(&data->forks[philo->id]);
}
