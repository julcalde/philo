/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:45:54 by julcalde          #+#    #+#             */
/*   Updated: 2025/05/04 18:55:58 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	routine_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	print_status(philo, "is eating");
	philo->meals_eaten++;
	philo->last_meal_time = get_time_msec();
	ft_usleep(data->time_to_eat, philo);
	if (get_is_dead(data))
		return (0);
	return (1);
}

void	routine_think(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	print_status(philo, "is thinking");
	if (data->num_philos % 2 == 0)
		ft_usleep(10, philo);
}

int	routine_sleep(t_philo	*philo)
{
	t_data	*data;

	data = philo->data;
	print_status(philo, "is sleeping");
	ft_usleep(data->time_to_sleep, philo);
	if (get_is_dead(data))
		return (0);
	return (1);
}
