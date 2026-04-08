/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 18:04:52 by erocha--          #+#    #+#             */
/*   Updated: 2026/04/08 19:12:21 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void eat(t_philosopher *philo)
{
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%d has taken a fork\n", philo->index);
	pthread_mutex_unlock(&philo->data->print_lock);
	pthread_mutex_lock(philo->r_fork);
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%d has taken a fork\n", philo->index);
	printf("%d is eating\n", philo->index);
	pthread_mutex_unlock(&philo->data->print_lock);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

static void sleep(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%d is sleeping\n", philo->index);
	pthread_mutex_unlock(&philo->data->print_lock);
	usleep(philo->data->time_to_sleep * 1000);
}

static void think(t_philosopher *philo)
{
	int	time_to_sleep;
	int	time_to_eat;
	int	time_to_die;

	time_to_sleep = philo->data->time_to_sleep;
	time_to_eat = philo->data->time_to_eat;
	time_to_die = philo->data->time_to_die;
	pthread_mutex_lock(&philo->data->print_lock);
	printf("%d is thinking\n", philo->index);
	pthread_mutex_unlock(&philo->data->print_lock);
	usleep(((time_to_die + (time_to_sleep + time_to_eat))/2) * 1000);
}

void	*routine(void *arg)
{
	t_philosopher	*philo;
	eat(philo);
	sleep(philo);
	tkink(philo);
	return (NULL);
}