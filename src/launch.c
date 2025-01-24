/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 19:57:59 by ptheo             #+#    #+#             */
/*   Updated: 2025/01/24 20:01:20 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_philo(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_philo)
	{
		pthread_create(&data->philo[i].thread, NULL, &philo_thread,
			&data->philo[i]);
		i++;
	}
	i = 0;
	master_thread(data);
	while (i < data->number_philo)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
	stop_thread(data);
	return (1);
}

int	one_philo(t_data *data)
{
	printf("0 0 is thinking\n");
	printf("0 0 has taken a fork\n");
	ft_usleep(data->time_to_die);
	printf("%ld 0 died\n", data->time_to_die);
}
