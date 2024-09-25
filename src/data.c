/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:30:21 by ptheo             #+#    #+#             */
/*   Updated: 2024/09/25 17:15:22 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_data(t_data *data)
{
	data->number = 0;
	data->philo = NULL;
	data->mutex = NULL;
	data->eat_all = NULL;
	data->end = 0;
	data->time_die = 0;
	data->time_eat = 0;
	data->number_eat = 0;
	data->limit = 0;
	data->time_sleep = 0;
	return (0);
}

int	full_data(t_data *data, int ac, char **av)
{
	data->number = ft_atoi(av[1]);
	data->time_die = ft_atoi(av[2]);
	data->time_eat = ft_atoi(av[3]);
	data->time_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		data->number_eat = ft_atoi(av[5]);
		data->limit = 1;
	}
	if (data->number == -1 || data->time_die == -1 || data->time_eat == -1
		|| data->number_eat == -1 || data->time_sleep == -1)
		return (ft_perror("Error argument"), -1);
	data->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* (data->number * 2));
	data->eat_all = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* (data->number));
	data->philo = init_philo(data, data->number);
	if (data->mutex == NULL || data->philo == NULL || data->eat_all == NULL)
		return (-1);
	return (0);
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	while (data->mutex != NULL && i < (data->number * 2))
	{
		pthread_mutex_unlock(&data->mutex[i]);
		pthread_mutex_destroy(&data->mutex[i]);
		i++;
	}
	free(data->mutex);
	i = 0;
	while (data->eat_all != NULL && i < data->number)
	{
		pthread_mutex_unlock(&data->eat_all[i]);
		pthread_mutex_destroy(&data->eat_all[i]);
		i++;
	}
	free(data->eat_all);
	i = 0;
	if (data->philo != NULL)
		free(data->philo);
}

void	print_data(t_data *data)
{
	int	i;

	i = 0;
	printf("number of philo : %d\ntime to die : %ld\ntime to eat : %ld\n",
		data->number, data->time_die, data->time_eat);
	printf("time to sleep : %ld\nnumber_eat : %ld\n",
		data->time_sleep, data->number_eat);
	while (i < data->number)
	{
		printf("philo %d : status -> %d time -> %d\n", data->philo[i].id,
			data->philo[i].status, 0);
		i++;
	}
}
