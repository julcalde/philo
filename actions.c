/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:45:54 by julcalde          #+#    #+#             */
/*   Updated: 2025/05/06 14:58:39 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	routine_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	take_forks(philo);
	philo->last_meal_time = get_time_msec();
	philo->meals_eaten++;
	print_status(philo, "is eating");
	ft_usleep(data->time_to_eat, philo);
	if (check_death(philo))
		return (0);
	routine_sleep(philo);
	return (1);
}

int	routine_think(t_philo *philo)
{
	if (check_death(philo))
		return (0);
	print_status(philo, "is thinking");
	return (1);
}

int	routine_sleep(t_philo	*philo)
{
	release_forks(philo);
	print_status(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep, philo);
	if (check_death(philo))
		return (0);
	if (!routine_think(philo))
		return (0);
	return (1);
}
