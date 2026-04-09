/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 15:15:46 by erocha--          #+#    #+#             */
/*   Updated: 2026/04/09 15:02:05 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef	struct s_data
{
	int				number_of_philosophers;
	int				eating_each_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long long		start_time;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	*forks;
	int				end;
}					t_data;

typedef struct s_philosopher
{
	int				index;
	pthread_t		tid;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t *r_fork;
	long long		last_meal;
	struct s_data	*data;
}					t_philosopher;

int			ft_atoi(const char *str);
int			ft_isdigit(int c);
long long	get_time();
void		*routine(void *arg);
void		*reaper(void *arg);

#endif