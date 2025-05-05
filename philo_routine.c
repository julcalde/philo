/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:30:12 by julcalde          #+#    #+#             */
/*   Updated: 2025/05/05 20:54:08 by julcalde         ###   ########.fr       */
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
	while (!get_is_dead(data))
	{
		if (data->required_meals != -1 && \
			philo->meals_eaten >= data->required_meals)
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
	if (check_death(philo))
		return (0);
	take_forks(philo);
	if (check_death(philo))
	{
		release_forks(philo);
		return (0);
	}
	if (!routine_eat(philo))
	{
		release_forks(philo);
		return (0);
	}
	release_forks(philo);
	if (!routine_sleep(philo))
		return (0);
	routine_think(philo);
	if (data->required_meals != -1 && \
		philo->meals_eaten >= data->required_meals)
		return (0);
	return (1);
}
