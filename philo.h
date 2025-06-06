/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julcalde <julcalde@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:29:55 by julcalde          #+#    #+#             */
/*   Updated: 2025/05/11 16:10:26 by julcalde         ###   ########.fr       */
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

# define USAGE_MSG "ERROR INVALID INPUT.\n\nInput 4 to 5 positive numbers.\n\n\
Instructions:\n\
./philo * ** *** **** *****\n\
* = [num_of_philos (1 - 200)]\n\
** = [time_to_die (60 - 2010)]\n\
*** = [time_to_eat (60 - 1000)]\n\
**** = [time_to_sleep (60 - 1000)]\n\
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
	pthread_mutex_t	monitor;
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

void		even_ph_id(t_philo *philo);
void		odd_ph_id(t_philo *philo);
void		take_forks(t_philo *philo);
void		release_forks(t_philo *philo);

// INITIALIZE.C

void		init_data(t_data *data, int argc, char **argv);
int			ft_atoi(const char *str);
int			ft_strcmp(const char *s1, const char *s2);

// MUTEX.C

int			init_mutexes(t_data *data);
void		destroy_mutexes(t_data *data);

// PHILO_ROUTINE.C

void		*philosopher_routine(void *arg);
int			perform_cycle(t_philo *philo);
void		loner_goner(t_philo *philo);

// THREADS.C

void		create_threads(t_data *data, t_philo *philos, pthread_t *threads);
void		init_ph_and_th(t_data *data, t_philo *philos, pthread_t *threads);
void		*monitor(void *arg);

// UTILS.C

long		get_time_msec(void);
void		print_status(t_philo *philo, const char *status);
int			check_death(t_philo *philo);
int			get_is_dead(t_data *data);
void		ft_usleep(long ms, t_philo *philo);

#endif
