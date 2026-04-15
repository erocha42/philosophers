/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/15 16:26:36 by erocha--          #+#    #+#             */
/*   Updated: 2026/04/15 16:28:35 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	one_philo_case(t_philosopher *philo)
{
	if (philo->data->nbr_of_philos == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		pthread_mutex_lock(&philo->data->print_lock);
		ft_printf("has taken a fork", philo);
		pthread_mutex_unlock(&philo->data->print_lock);
		usleep(philo->data->time_to_die * 1000);
		pthread_mutex_unlock(philo->l_fork);
		return (1);
	}
	return (0);
}

int	end_checker(t_philosopher *philo, pthread_mutex_t *first,
	pthread_mutex_t *second)
{
	pthread_mutex_lock(first);
	pthread_mutex_lock(&philo->data->end_lock);
	if (philo->data->end)
	{
		pthread_mutex_unlock(first);
		pthread_mutex_unlock(&philo->data->end_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->end_lock);
	pthread_mutex_lock(second);
	pthread_mutex_lock(&philo->data->end_lock);
	if (philo->data->end)
	{
		pthread_mutex_unlock(first);
		pthread_mutex_unlock(second);
		pthread_mutex_unlock(&philo->data->end_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->end_lock);
	return (0);
}
