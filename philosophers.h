/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 15:15:46 by erocha--          #+#    #+#             */
/*   Updated: 2026/04/15 16:57:41 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int				nbr_of_philos;
	int				eating_each_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long long		start_time;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	end_lock;
	pthread_mutex_t	*forks;
	int				end;
}					t_data;

typedef struct s_philosopher
{
	int				index;
	pthread_t		tid;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	meal_lock;
	long long		last_meal;
	int				nbr_meal;
	struct s_data	*data;
}					t_philosopher;

int			ft_atoi(const char *str);
int			ft_isdigit(int c);
long long	get_time(void);
int			o_digits_checker(int argc, char **argv);
void		ft_printf(char *str, t_philosopher *philo);
void		*routine(void *arg);
void		*reaper(void *arg);
int			end_checker(t_philosopher *philo, pthread_mutex_t *first,
				pthread_mutex_t *second);
int			one_philo_case(t_philosopher *philo);

#endif