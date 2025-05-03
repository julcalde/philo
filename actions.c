/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 20:45:54 by julcalde          #+#    #+#             */
/*   Updated: 2025/05/03 21:01:04 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	routine_eat(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	print_status(philo, "is eating");
	philo->last_meal_time = get_time_msec();
	philo->meals_eaten++;
	ft_usleep(data->time_to_eat, philo);
}

void	routine_think(t_philo *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->num_philos % 2 == 0)
		ft_usleep(10, philo);
	print_status(philo, "is thinking");
}

void	routine_sleep(t_philo	*philo)
{
	t_data	*data;

	data = philo->data;
	print_status(philo, "is sleeping");
	ft_usleep(data->time_to_sleep, philo);
}
