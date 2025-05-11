/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:29:19 by julcalde          #+#    #+#             */
/*   Updated: 2025/05/11 16:09:18 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	threads[200];
	pthread_t	monitor_thread;
	t_philo		philos[200];

	if (argc < 5 || argc > 6)
		return (printf(USAGE_MSG), EXIT_FAILURE);
	init_data(&data, argc, argv);
	pthread_create(&monitor_thread, NULL, monitor, philos);
	init_ph_and_th(&data, philos, threads);
	pthread_join(monitor_thread, NULL);
	destroy_mutexes(&data);
	free(data.forks);
	return (0);
}
