/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 18:04:52 by erocha--          #+#    #+#             */
/*   Updated: 2026/04/09 18:55:48 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void eat_action(t_philosopher *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t *second;

	first = philo->l_fork;
	second = philo->r_fork;
	if (philo->index % 2 == 1)
	{
		first = philo->r_fork;
		second = philo->l_fork;
	}
	pthread_mutex_lock(first);
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%lld %d has taken a fork\n", philo->data->start_time, philo->index);
	pthread_mutex_unlock(&philo->data->print_lock);
	pthread_mutex_lock(second);
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%lld %d has taken a fork\n", philo->data->start_time, philo->index);
	printf("%lld %d is eating\n", philo->data->start_time, philo->index);
	pthread_mutex_unlock(&philo->data->print_lock);
	pthread_mutex_lock(&philo->data->meal_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->data->meal_lock);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(first);
	pthread_mutex_unlock(second);
}

static void sleep_action(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%lld %d is sleeping\n", philo->data->start_time, philo->index);
	pthread_mutex_unlock(&philo->data->print_lock);
	usleep(philo->data->time_to_sleep * 1000);
}

static void think_action(t_philosopher *philo)
{
	int	time_to_sleep;
	int	time_to_eat;
	int	time_to_die;

	time_to_sleep = philo->data->time_to_sleep;
	time_to_eat = philo->data->time_to_eat;
	time_to_die = philo->data->time_to_die;
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%lld %d is thinking\n", philo->data->start_time, philo->index);
	pthread_mutex_unlock(&philo->data->print_lock);
	usleep(((time_to_die - (time_to_sleep + time_to_eat))/2) * 1000);
}

static int	check_end(t_philosopher *philo)
{
	int	res;
	pthread_mutex_lock(&philo->data->meal_lock);
	res = philo->data->end;
	pthread_mutex_unlock(&philo->data->meal_lock);
	return (res);
}

void	*routine(void *arg)
{
	t_philosopher	*philo;
	int				i;

	philo = (t_philosopher *)arg;
	if (philo->data->number_of_philosophers == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		printf("%lld %d has taken a fork\n", get_time() - philo->data->start_time, philo->index);
		usleep(philo->data->time_to_die * 1000);
		pthread_mutex_unlock(philo->l_fork);
		return (NULL);
	}
	i = 0;
	while (1)
	{
		if (check_end(philo))
			break ;
		eat_action(philo);
		if (check_end(philo))
			break ;
		sleep_action(philo);
		if (check_end(philo))
			break ;
		think_action(philo);
		i++;
	}
	return (NULL);
}
