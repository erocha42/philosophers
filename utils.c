/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erocha-- <erocha--@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 15:57:33 by erocha--          #+#    #+#             */
/*   Updated: 2026/04/15 16:59:12 by erocha--         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	nbr;
	int	less_counter;

	i = 0;
	nbr = 0;
	less_counter = 0;
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] && (str[i] == '+' || str[i] == '-'))
	{
		if (str[i] == '-')
			less_counter++;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + (str[i] - 48);
		i++;
	}
	if (less_counter % 2 == 1)
		nbr = nbr * -1;
	return (nbr);
}

int	ft_isdigit(int c)
{
	if (c < '0' || c > '9')
		return (0);
	return (1);
}

long long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	o_digits_checker(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]) || argv[1][0] == '0' ||
				(argc == 6 && argv[5][0] == '0'))
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

void	ft_printf(char *str, t_philosopher *philo)
{
	printf("%lld %d %s\n", get_time() - philo->data->start_time,
		philo->index, str);
}
