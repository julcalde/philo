/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:29:19 by julcalde          #+#    #+#             */
/*   Updated: 2025/05/06 21:32:01 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data		data ;
	pthread_t	threads[200];
	t_philo		philos[200];
	int			i;

	i = 0;
	if (argc < 5 || argc > 6)
		return (printf (USAGE_MSG), EXIT_FAILURE);
	init_data(&data, argc, argv);
	while (i < data.num_philos)
	{
		philos[i].id = i;
		philos[i].data = &data;
		philos[i].last_meal_time = data.start_time - data.time_to_eat;
		philos[i].meals_eaten = 0;
		i++;
	}
	create_threads(&data, philos, threads);
	join_threads(&data, threads);
	destroy_mutexes(&data);
	free(data.forks);
	return (0);
}
