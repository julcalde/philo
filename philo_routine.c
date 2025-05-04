/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:30:12 by julcalde          #+#    #+#             */
/*   Updated: 2025/05/04 16:01:24 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	perform_cycle(t_philo *philo);


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

static int	perform_cycle(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	routine_think(philo);
	philo->last_meal_time = get_time_msec();
	take_forks(philo);
	if (data->num_philos == 1)
	{
		release_forks(philo);
		if (check_death(philo))
			return (0);
		return (1);
	}
	if (check_death(philo))
		return (0);
	routine_eat(philo);
	release_forks(philo);
	if (check_death(philo))
		return (0);
	routine_sleep(philo);
	if (data->required_meals != -1 && \
		philo->meals_eaten >= data->required_meals)
		return (0);
	return (1);
}
