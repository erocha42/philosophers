/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 12:27:51 by erocha--          #+#    #+#             */
/*   Updated: 2026/04/15 17:13:12 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	nbr_eat_check(t_philosopher *philos)
{
	int	i;

	i = 0;
	if (philos[0].data->eating_each_philo <= 0)
		return (0);
	while (i < philos[0].data->nbr_of_philos)
	{
		pthread_mutex_lock(&philos[i].meal_lock);
		if (philos[i].nbr_meal < philos[0].data->eating_each_philo)
		{
			pthread_mutex_unlock(&philos[i].meal_lock);
			return (0);
		}
		pthread_mutex_unlock(&philos[i].meal_lock);
		i++;
	}
	return (1);
}

static int	die_checker(t_philosopher *philo)
{
	if (get_time() - philo->last_meal > philo->data->time_to_die)
	{
		pthread_mutex_lock(&philo->data->end_lock);
		pthread_mutex_lock(&philo->data->print_lock);
		ft_printf("died", philo);
		pthread_mutex_unlock(&philo->data->print_lock);
		philo->data->end = 1;
		pthread_mutex_unlock(&philo->data->end_lock);
		pthread_mutex_unlock(&philo->meal_lock);
		return (1);
	}
	return (0);
}

void	*reaper(void *arg)
{
	t_philosopher	*philos;
	int				i;

	philos = (t_philosopher *) arg;
	while (1)
	{
		i = 0;
		while (i < philos[0].data->nbr_of_philos)
		{
			pthread_mutex_lock(&philos[i].meal_lock);
			if (die_checker(&philos[i]))
				return (NULL);
			pthread_mutex_unlock(&philos[i].meal_lock);
			i++;
		}
		if (nbr_eat_check(philos))
		{
			pthread_mutex_lock(&philos->data->end_lock);
			philos[0].data->end = 1;
			pthread_mutex_unlock(&philos->data->end_lock);
			return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
