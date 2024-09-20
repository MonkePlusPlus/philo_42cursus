/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 21:31:32 by ptheo             #+#    #+#             */
/*   Updated: 2024/09/20 21:51:45 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	philo_death(t_data *data)
{
	size_t	time;
	int		i;

	i = 0;
	time = get_current_time();
	while (i < data->number)
	{
		if (data->philo[i].status == THINKING
			&& time - data->philo[i].time_think >= data->time_die)
		{
			printf("%ld : %d died\n", time - data->time, data->philo[i].id + 1);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*master_game(void *arg)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data *)arg;
	while (i < data->number)
	{
		pthread_create(&data->philo[i].thread, NULL, &philo_journey, &data->philo[i]);
		i++;
	}
	while (data->end == 0)
	{
		if (philo_death(data))
		{
			data->end = 1;
			i = 0;
			while (i < data->number)
			{
				pthread_detach(data->philo[i].thread);
				i++;
			}
		}
	}
	i = -1;
	while (++i < data->number)
		pthread_join(data->philo[i].thread, NULL);
	return (NULL);
}
