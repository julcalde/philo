/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:30:12 by julcalde          #+#    #+#             */
/*   Updated: 2025/05/01 16:14:39 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eat(t_philo *philo)
{
	t_data	*data;
	long	now;

	data = philo->data;
	now = get_time_msec();
	philo->last_meal_time = now;
	print_status(philo, "is eating");
	philo->meals_eaten += 1;
	usleep(data->time_to_eat * 1000);
}

static void	think(t_philo *philo)
{
	print_status(philo, "is thinking");
}

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
		think(philo);
		take_forks(philo);
		if (data->num_philos == 1)
		{
			release_forks(philo);
			break ;
		}
		if (check_death(philo))
			break ;
		eat(philo);
		release_forks(philo);
		if (check_death(philo))
			break ;
		print_status(philo, "is sleeping");
		ft_usleep(data->time_to_sleep, philo);
		if (required_meals != -1 && philo->meals_eaten >= required_meals)
			break ;
	}
	return (NULL);
}

void	ft_usleep(long ms, t_philo *philo)
{
	long	start;

	start = get_time_msec();
	while ((get_time_msec() - start) < ms && !get_is_dead(philo->data))
		usleep(500);
}
