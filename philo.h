/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:29:55 by julcalde          #+#    #+#             */
/*   Updated: 2025/05/06 14:52:05 by julcalde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "philo.h"
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

# define USAGE_MSG "ERROR INVALID INPUT.\nPROPER INPUT VALUES:\n\
./philo * ** *** **** *****\n\
* = [num_of_philos (1 - 200)]\n\
** = [time_to_die (60+)]\n\
*** = [time_to_eat (60+)]\n\
**** = [time_to_sleep (60+)]\n\
***** = [optional_limit_of_meals (1+)]\n\n\
Example usage: ./philo 5 800 200 200 3\n"

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				required_meals;
	volatile int	is_dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	dead_mutex;
	long			start_time;
}		t_data;

typedef struct s_philo
{
	int		id;
	long	last_meal_time;
	int		meals_eaten;
	t_data	*data;
}		t_philo;

// ACTIONS.C

int			routine_eat(t_philo *philo);
int			routine_think(t_philo *philo);
int			routine_sleep(t_philo *philo);

// FORKS.C

void		take_forks(t_philo *philo);
void		release_forks(t_philo *philo);

// INITIALIZE.C

void		init_data(t_data *data, int argc, char **argv);
int			ft_atoi(const char *str);

// MUTEX.C

void		init_mutexes(t_data *data);
void		destroy_mutexes(t_data *data);


// PHILO_ROUTINE.C

void		*philosopher_routine(void *arg);
int			perform_cycle(t_philo *philo);
void		loner_goner(t_philo *philo);

// THREADS.C

void		create_threads(t_data *data, t_philo *philos, \
			pthread_t *threads);
void		join_threads(t_data *data, pthread_t *threads);


// UTILS.C

long		get_time_msec(void);
void		print_status(t_philo *philo, const char *status);
int			check_death(t_philo *philo);
int			get_is_dead(t_data *data);
void		ft_usleep(long ms, t_philo *philo);


#endif
