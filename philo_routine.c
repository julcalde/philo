/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:30:12 by julcalde          #+#    #+#             */
/*   Updated: 2025/05/04 18:54:23 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;
	int		required_meals;

	philo = (t_philo *)arg;
	data = philo->data;
	required_meals = data->required_meals;
	while (!get_is_dead(data))
	{
		if (required_meals != -1 && philo->meals_eaten >= required_meals)
			break ;
		if (!perform_cycle(philo))
			break ;
	}
	return (NULL);
}

int	perform_cycle(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	routine_think(philo);
	if (data->num_philos == 1)
	{
		take_forks(philo);
		release_forks(philo);
		if (check_death(philo))
			return (0);
		return (1);
	}
	take_forks(philo);
	if (check_death(philo))
		return (0);
	if (!routine_eat(philo))
		return (0);
	release_forks(philo);
	if (!routine_sleep(philo))
		return (0);
	if (data->required_meals != -1 && \
		philo->meals_eaten >= data->required_meals)
		return (0);
	return (1);
}

int	try_even_philo(t_philo *philo, int first, int second)
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

int	try_odd_philo(t_philo *philo, int first, int second)
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
