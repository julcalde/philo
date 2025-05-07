/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:45:54 by julcalde          #+#    #+#             */
/*   Updated: 2025/05/07 17:16:29 by julcalde         ###   ########.fr       */
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
	release_forks(philo);
	return (check_death(philo));
}

int	routine_sleep(t_philo *philo)
{
	if (get_is_dead(philo->data))
		return (0);
	print_status(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep, philo);
	return (check_death(philo));
}

int	routine_think(t_philo *philo)
{
	if (get_is_dead(philo->data))
		return (0);
	print_status(philo, "is thinking");
	ft_usleep(1, philo);
	return (check_death(philo));
}
