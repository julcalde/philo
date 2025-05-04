/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:30:32 by julcalde          #+#    #+#             */
/*   Updated: 2025/05/04 17:02:30 by julcalde         ###   ########.fr       */
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

	current_time = get_time_msec();
	if (current_time - philo->last_meal_time >= philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->dead_mutex);
		if (!philo->data->is_dead)
		{
			philo->data->is_dead = 1;
			print_status(philo, "died");
		}
		pthread_mutex_unlock(&philo->data->dead_mutex);
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

void	ft_usleep(long ms, t_philo *philo)
{
	long	start;

	start = get_time_msec();
	while (get_time_msec() - start < ms && !get_is_dead(philo->data))
		usleep(100);
}
