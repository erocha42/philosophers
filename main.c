/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 15:14:34 by erocha--          #+#    #+#             */
/*   Updated: 2026/04/09 17:19:55 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	args_check(int argc, char **argv)
{
	int	i;
	int	j;
	
	i = 1;
	if (argc != 6 && argc != 5)
	{
		if (argc < 5)
			write(2, "Philo requires 4 arguments minimum\n", 36);
		else
			write(2, "Too many arguments\n", 20);
		return (0);
	}
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
			{
				write(2, "An argument is not only digits or invalid\n", 43);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

static void	data_init(t_data *data, int argc, char **argv)
{
	int	i;

	i = 0;
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->eating_each_philo = ft_atoi(argv[5]);
	else
		data->eating_each_philo = -1;
	data->start_time = get_time();
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	while (i < data->number_of_philosophers)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
	data->end = 0;
}

static void	philos_init(t_philosopher *philos, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		philos[i].data = data;
		philos[i].index = i + 1;
		philos[i].l_fork = &data->forks[i];
		philos[i].r_fork = &data->forks[(i + 1) % data->number_of_philosophers];
		philos[i].last_meal = data->start_time;
		i++;
	}
}

static void cleaning(t_philosopher *philos)
{
	int	i;

	i = 0;
	while (i < philos->data->number_of_philosophers)
	{
		pthread_join(philos[i].tid, NULL);
		i++;
	}
	i = 0;
	while (i < philos->data->number_of_philosophers)
	{
		pthread_mutex_destroy(&philos->data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&philos->data->print_lock);
	pthread_mutex_destroy(&philos->data->meal_lock);
	free(philos->data->forks);
	free(philos);
}

int	main(int argc, char **argv)
{
	t_philosopher	*philos;
	pthread_t		monitor_id;
	t_data			data;
	int				i;

	i = 0;
	if (!args_check(argc, argv))
		return (1);
	philos = malloc(sizeof(t_philosopher) * ft_atoi(argv[1]));
	data_init(&data, argc, argv);
	philos_init(philos, &data);
	while (i < data.number_of_philosophers)
	{
		pthread_create(&philos[i].tid, NULL, routine, &philos[i]);
		i++;
	}
	pthread_create(&monitor_id, NULL, reaper, philos);
	pthread_join(monitor_id, NULL);
	cleaning(philos);
	return (0);
}
