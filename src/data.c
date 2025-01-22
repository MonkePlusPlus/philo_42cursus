/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:30:21 by ptheo             #+#    #+#             */
/*   Updated: 2025/01/22 04:03:40 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_data(t_data *data, int ac, char **av)
{
	data->number_philo = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	data->number_of_time = -1;
	if (ac == 6)
		data->number_of_time = ft_atoi(av[5]);
	if (data->number_philo == 0 || data->time_to_die == 0
		|| data->time_to_eat == 0 || data->time_to_sleep == 0
		|| data->number_of_time == 0)
		return (-1);
	if (init_philo(data) == -1)
		return (-1);
	return (0);
}

int	init_philo(t_data *data)
{
	size_t	time;
	int		i;

	time = get_current_time();
	data->philo = malloc(sizeof(t_philo) * data->number_philo);
	data->mutex = malloc(sizeof(t_philo) * data->number_philo);
	if (data->philo == NULL || data->mutex == NULL)
		return (-1);
	i = 0;
	while (i < data->number_philo)
	{
		if (pthread_mutex_init(&data->mutex[i], NULL) != 0)
			return (-1);
		i++;
	}
	i = 0;
	while (i < data->number_philo)
	{
		data->philo[i].id = i;
		data->philo[i].start_time = time;
		data->philo[i].time_think = -1;
		data->philo[i].finish = 0;
		data->philo[i].right = &data->mutex[i];
		if (i != 0)
			data->philo[i].left = &data->mutex[i - 1];
		if (pthread_mutex_init(&data->philo[i].var, NULL) != 0)
				return (-1);
		data->philo[i].data = data;
		i++;
	}
	data->philo[0].left = &data->mutex[data->number_philo - 1];
	return (0);
}

void	free_data(t_data *data)
{
	int	i;

	if (data->philo != NULL)
	{
		i = 0;
		while (i < data->number_philo)
		{
			i++;
		}
		free(data->philo);
	}
	if (data->mutex != NULL)
	{
		i = 0;
		while (i < data->number_philo)
		{
			pthread_mutex_unlock(&data->mutex[i]);
			pthread_cancel(data->philo[i].thread);
			pthread_mutex_destroy(&data->mutex[i]);
			i++;
		}
		free(data->mutex);
	}
	return ;
}
