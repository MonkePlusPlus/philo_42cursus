/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:30:21 by ptheo             #+#    #+#             */
/*   Updated: 2024/09/20 19:02:38 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	init_data(t_data *data)
{
	data->number = 0;
	data->philo = NULL;
	data->mutex = NULL;
	data->end = 0;
	data->time_die = 0;
	data->time_eat = 0;
	data->time_number = 0;
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
		data->time_number = ft_atoi(av[5]);
	if (data->number == -1 || data->time_die == -1 || data->time_eat == -1
		|| data->time_number == -1 || data->time_sleep == -1)
		return (ft_perror("Error argument"), -1);
	data->mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (data->number + 1));
	if (data->mutex == NULL)
		return (-1);
	data->philo = init_philo(data, data->number);
	if (data->philo == NULL)
		return (-1);
	if (pthread_mutex_init(&data->mutex[data->number], NULL) != 0)
		return (-1);
	return (0);
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	if (data->mutex != NULL)
	{
		while (i < data->number + 1)
		{
			pthread_mutex_destroy(&data->mutex[i]);
			i++;
		}
		free(data->mutex);
	}
	i = 0;
	if (data->philo != NULL)
	{
		while (i < data->number)
		{
			pthread_detach(data->philo[i].thread);
			i++;
		}
		free(data->philo);
	}
}

void    print_data(t_data *data)
{
	int	i;

	i = 0;
	printf("number of philo : %d\ntime to die : %ld\ntime to eat : %ld\n",
		data->number, data->time_die, data->time_eat);
	printf("time to sleep : %ld\ntime number : %d\n",
		data->time_sleep, data->time_number);
	while (i < data->number)
	{
		printf("philo %d : status -> %d time -> %ld\n",
			data->philo[i].id, data->philo[i].status, 
			0);
		i++;
	}
}
