// File: philo_routine.c

# include "philo.h"
# include <unistd.h>
# include <stdlib.h>

void	take_forks(t_philo *philo)
{
    t_data	*data;
    int		left;
    int		right;

    data = philo->data;
    left = philo->id;
    right = (philo->id + 1) % data->num_philos;
    if (data->num_philos == 1)
    {
        pthread_mutex_lock(&data->forks[left]);
        print_status(philo, "has taken a fork");
        return ;
    }
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(&data->forks[right]);
        print_status(philo, "has taken a fork");
        pthread_mutex_lock(&data->forks[left]);
    }
    else
    {
        pthread_mutex_lock(&data->forks[left]);
        print_status(philo, "has taken a fork");
        pthread_mutex_lock(&data->forks[right]);
    }
    print_status(philo, "has taken a fork");
}

void	release_forks(t_philo *philo)
{
    t_data	*data;
    int		left;
    int		right;

    data = philo->data;
    left = philo->id;
    right = (philo->id + 1) % data->num_philos;
    if (data->num_philos == 1)
    {
        pthread_mutex_unlock(&data->forks[left]);
        return ;
    }
    pthread_mutex_unlock(&data->forks[left]);
    pthread_mutex_unlock(&data->forks[right]);
}

void	eat(t_philo *philo)
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

void	think(t_philo *philo)
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
        usleep(data->time_to_sleep * 1000);
        if (required_meals != -1 && philo->meals_eaten >= required_meals)
            break ;
    }
    return (NULL);
}
