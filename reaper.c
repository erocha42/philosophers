/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reaper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 12:27:51 by erocha--          #+#    #+#             */
/*   Updated: 2026/04/09 15:47:54 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*reaper(void *arg)
{
	t_philosopher	*philos;
	int				i;

	philos = (t_philosopher *) arg;
	while (1)
	{
		i = 0;
		while (i < philos[0].data->number_of_philosophers)
		{
			pthread_mutex_lock(&philos[i].data->meal_lock);
			if (get_time() - philos[i].last_meal > philos[i].data->time_to_die)
			{
				pthread_mutex_lock(&philos[i].data->print_lock);
				printf("%lld %d is died\n", get_time() - philos[i].data->start_time, philos[i].index);
				philos[i].data->end = 1;
				pthread_mutex_unlock(&philos[i].data->print_lock);
				pthread_mutex_unlock(&philos[i].data->meal_lock);
				return (NULL);
			}
			pthread_mutex_unlock(&philos[i].data->meal_lock);
			i++;
		}
		usleep(1000);
	}
	return (NULL);
}
