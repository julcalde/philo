/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:45:54 by julcalde          #+#    #+#             */
/*   Updated: 2025/05/06 23:25:57 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	routine_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (get_is_dead(data))
		return (0);
	take_forks(philo);
	if (get_is_dead(data))
	{
		release_forks(philo);
		return (0);
	}
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
	print_status(philo, "is thinking");
	ft_usleep(1, philo);
	if (check_death(philo))
		return (0);
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
