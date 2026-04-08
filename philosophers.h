/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 15:15:46 by erocha--          #+#    #+#             */
/*   Updated: 2026/04/08 19:06:56 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

typedef	struct s_data
{
	int				number_of_philosophers;
	int				eating_each_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	*forks;
}					t_data;

typedef struct s_philosopher
{
	int				index;
	pthread_t		tid;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t *r_fork;
	struct s_data	*data;
}					t_philosopher;

int		ft_atoi(const char *str);
int		ft_isdigit(int c);
void	*routine(void *arg);

#endif