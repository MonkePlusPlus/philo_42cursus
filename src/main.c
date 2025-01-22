/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:56:32 by ptheo             #+#    #+#             */
/*   Updated: 2025/01/22 03:44:18 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	start_philo(t_data *data)
{
	int	i;

	i = 0;
	pthread_create(&data->master, NULL, &master_thread, data);
	while (i < data->number_philo)
	{
		pthread_create(&data->philo[i].thread, NULL, &philo_thread, &data->philo[i]);
		i++;
	}
	pthread_join(data->master, NULL);
	i = 0;
	while (i < data->number_philo)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	i = 0;
	if (ac == 5 || ac == 6)
	{
		if (init_data(&data, ac, av) == -1)
			return (free_data(&data), -1);
		start_philo(&data);
	}
	else
		return (ft_perror("Error number argument"), -1);
	return (0);
}
