/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:29:19 by julcalde          #+#    #+#             */
/*   Updated: 2025/05/07 19:22:40 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor(void *arg)
{
	t_philo	*philos;
	t_data	*data;
	int		i;
	int		done;

	philos = (t_philo *)arg;
	data = philos[0].data;
	while (!get_is_dead(data))
	{
		// printf("1\n");
		if (data->required_meals != -1)
		{
			done = 1;
			i = 0;
			while (i < data->num_philos)
			{
				// printf("2\n");
				if (philos[i].meals_eaten < data->required_meals)
					done = 0;
				i++;
			}
			if (done)
				return (NULL);
		}
		i = 0;
		while (i < data->num_philos)
		{
			// printf("3\n");
			if (check_death(&philos[i]))
			{
				// printf("4\n");
				return (NULL);
			}
			i++;
		}
		usleep(1000);
	}
	return (NULL);
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
	create_threads(data, philos, threads);// After here mutexes should be exited before detatching
	i = 0;
	while (i < data->num_philos)
	{
		printf("Exiting TID: %d.\n", (int)threads[i]);
		pthread_join(threads[i], NULL);// exits at the end, but before the dying thread
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	threads[200];
	pthread_t	monitor_thread;
	t_philo		philos[200];

	if (argc < 5 || argc > 6)
		return (printf(USAGE_MSG), EXIT_FAILURE);
	init_data(&data, argc, argv);
	init_ph_and_th(&data, philos, threads);
	pthread_create(&monitor_thread, NULL, monitor, philos);
	// join_threads(&data, threads);
	pthread_join(monitor_thread, NULL);
	// printf("Monitor thread joined.\n");
	// usleep(1000);
	destroy_mutexes(&data);
	free(data.forks);
	return (0);
}
