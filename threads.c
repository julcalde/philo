/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 15:18:24 by julcalde          #+#    #+#             */
/*   Updated: 2025/05/11 16:12:41 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	create_threads(t_data *data, t_philo *philos, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&threads[i], NULL, philosopher_routine,
				&philos[i]) != 0)
		{
			perror("pthread_create");
			data->is_dead = 1;
			return ;
		}
		i++;
	}
}

void	init_ph_and_th(t_data *data, t_philo *philos, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		philos[i].id = i;
		philos[i].data = data;
		philos[i].last_meal_time = data->start_time - data->time_to_eat;
		philos[i].meals_eaten = 0;
		i++;
	}
	create_threads(data, philos, threads);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}

// void	*monitor(void *arg)
// {
// 	t_philo	*philos;
// 	t_data	*data;
// 	int		i;
// 	int		done;

// 	philos = (t_philo *)arg;
// 	data = philos[0].data;
// 	while (!get_is_dead(data))
// 	{
// 		if (data->required_meals != -1)
// 		{
// 			done = 1;
// 			i = 0;
// 			while (i < data->num_philos)
// 			{
// 				if (philos[i].meals_eaten < data->required_meals)
// 					done = 0;
// 				i++;
// 			}
// 			if (done)
// 			{
// 				pthread_mutex_lock(&data->dead_mutex);
// 				data->is_dead = 1;
// 				pthread_mutex_unlock(&data->dead_mutex);
// 				return (NULL);
// 			}
// 		}
// 		i = 0;
// 		while (i < data->num_philos)
// 		{
// 			if (check_death(&philos[i]))
// 				return (NULL);
// 			i++;
// 		}
// 		usleep(100);
// 	}
// 	return (NULL);
// }

static int	check_all_ate_enough(t_philo *philos, t_data *data)
{
	int	i;

	if (data->required_meals == -1)
		return (0);
	i = 0;
	while (i < data->num_philos)
	{
		if (philos[i].meals_eaten < data->required_meals)
			return (0);
		i++;
	}
	return (1);
}

static int	check_philosophers_death(t_philo *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (check_death(&philos[i]))
			return (1);
		i++;
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_philo	*philos;
	t_data	*data;

	philos = (t_philo *)arg;
	data = philos[0].data;
	while (!get_is_dead(data))
	{
		if (check_all_ate_enough(philos, data))
		{
			pthread_mutex_lock(&data->dead_mutex);
			data->is_dead = 1;
			pthread_mutex_unlock(&data->dead_mutex);
			return (NULL);
		}
		if (check_philosophers_death(philos, data))
			return (NULL);
		usleep(100);
	}
	return (NULL);
}
