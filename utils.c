/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:30:32 by julcalde          #+#    #+#             */
/*   Updated: 2025/05/01 15:28:56 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time_msec(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long)(tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	print_status(t_philo *philo, const char *status)
{
	long	current_time;

	current_time = get_time_msec() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("%ld %d %s\n", current_time, philo->id + 1, status);
	pthread_mutex_unlock(&philo->data->print_mutex);
}

int	check_death(t_philo *philo)
{
	long	current_time;
	long	death_time;
	t_data	*data;

	data = philo->data;
	current_time = get_time_msec();
	death_time = philo->last_meal_time + data->time_to_eat + data->time_to_die;
	if (current_time >= death_time)
	{
		pthread_mutex_lock(&data->dead_mutex);
		if (!data->is_dead)
		{
			data->is_dead = 1;
			print_status(philo, "died");
		}
		pthread_mutex_unlock(&data->dead_mutex);
		return (1);
	}
	return (0);
}

int	get_is_dead(t_data *data)
{
	int	is_dead;

	pthread_mutex_lock(&data->dead_mutex);
	is_dead = data->is_dead;
	pthread_mutex_unlock(&data->dead_mutex);
	return (is_dead);
}
