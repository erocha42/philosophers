/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 18:04:52 by erocha--          #+#    #+#             */
/*   Updated: 2026/04/15 17:26:30 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	eat_action(t_philosopher *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;

	first = philo->l_fork;
	second = philo->r_fork;
	if (philo->index % 2 == 1)
	{
		first = philo->r_fork;
		second = philo->l_fork;
	}
	if (end_checker(philo, first, second))
		return (0);
	pthread_mutex_lock(&philo->data->print_lock);
	ft_printf("has taken a fork", philo);
	ft_printf("has taken a fork", philo);
	ft_printf("is eating", philo);
	pthread_mutex_unlock(&philo->data->print_lock);
	pthread_mutex_lock(&philo->meal_lock);
	philo->last_meal = get_time();
	philo->nbr_meal++;
	pthread_mutex_unlock(&philo->meal_lock);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(first);
	pthread_mutex_unlock(second);
	return (1);
}

static void	sleep_action(t_philosopher *philo)
{
	pthread_mutex_lock(&philo->data->print_lock);
	ft_printf("is sleeping", philo);
	pthread_mutex_unlock(&philo->data->print_lock);
	usleep(philo->data->time_to_sleep * 1000);
}

static void	think_action(t_philosopher *philo)
{
	int	time_to_sleep;
	int	time_to_eat;
	int	time_to_die;

	time_to_sleep = philo->data->time_to_sleep;
	time_to_eat = philo->data->time_to_eat;
	time_to_die = philo->data->time_to_die;
	pthread_mutex_lock(&philo->data->print_lock);
	ft_printf("is thinking", philo);
	pthread_mutex_unlock(&philo->data->print_lock);
	if ((time_to_sleep + time_to_eat) < time_to_die)
		usleep(((time_to_die - (time_to_sleep + time_to_eat)) / 2) * 1000);
	else
		usleep(1000);
}

static int	check_end(t_philosopher *philo)
{
	int	res;

	pthread_mutex_lock(&philo->data->end_lock);
	res = philo->data->end;
	pthread_mutex_unlock(&philo->data->end_lock);
	return (res);
}

void	*routine(void *arg)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)arg;
	if (one_philo_case(philo))
		return (NULL);
	if (philo->index % 2 == 0)
		usleep(philo->data->time_to_eat * 500);
	while (1)
	{
		if (check_end(philo))
			break ;
		if (!eat_action(philo))
			break ;
		if (check_end(philo))
			break ;
		sleep_action(philo);
		if (check_end(philo))
			break ;
		think_action(philo);
	}
	return (NULL);
}
