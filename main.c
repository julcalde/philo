/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:29:19 by julcalde          #+#    #+#             */
/*   Updated: 2025/05/01 14:29:40 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		main(int argc, char **argv)
{
    t_data		data;
    pthread_t	threads[200];
    t_philo		philos[200];
    int			i;

    i = 0;
    if (argc < 5 || argc > 6)
    {
        printf("Usage: %s number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n", argv[0]);
        return (1);
    }
    data.num_philos = atoi(argv[1]);
    data.time_to_die = atoi(argv[2]);
    data.time_to_eat = atoi(argv[3]);
    data.time_to_sleep = atoi(argv[4]);
    data.required_meals = argc == 6 ? atoi(argv[5]) : -1;
    data.is_dead = 0;
    data.forks = malloc(sizeof(pthread_mutex_t) * data.num_philos);
    init_mutexes(&data);
    data.start_time = get_time_msec();
    i = 0;
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

void	init_mutexes(t_data *data)
{
    int	i;

    i = 0;
    while (i < data->num_philos)
    {
        pthread_mutex_init(&data->forks[i], NULL);
        i++;
    }
    pthread_mutex_init(&data->print_mutex, NULL);
    pthread_mutex_init(&data->dead_mutex, NULL);
}

void	destroy_mutexes(t_data *data)
{
    int	i;

    i = 0;
    while (i < data->num_philos)
    {
        pthread_mutex_destroy(&data->forks[i]);
        i++;
    }
    pthread_mutex_destroy(&data->print_mutex);
    pthread_mutex_destroy(&data->dead_mutex);
}

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

void	join_threads(t_data *data, pthread_t *threads)
{
    int	i;

    i = 0;
    while (i < data->num_philos)
    {
        pthread_join(threads[i], NULL);
        i++;
    }
}
