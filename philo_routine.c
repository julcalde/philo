/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:30:12 by julcalde          #+#    #+#             */
/*   Updated: 2025/05/03 21:12:19 by julcalde         ###   ########.fr       */
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
		routine_think(philo);
		take_forks(philo);
		if (data->num_philos == 1)
		{
			release_forks(philo);
			if (check_death(philo))
				break ;
			continue ;
		}
		if (check_death(philo))
			break ;
		routine_eat(philo);
		release_forks(philo);
		if (check_death(philo))
			break ;
		routine_sleep(philo);
		if (required_meals != -1 && philo->meals_eaten >= required_meals)
			break ;
	}
	return (NULL);
}
