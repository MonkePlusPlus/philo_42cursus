/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 21:31:32 by ptheo             #+#    #+#             */
/*   Updated: 2024/09/22 18:51:59 by ptheo            ###   ########.fr       */
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
			&& (time - data->philo[i].time_think) >= data->time_die)
		{
			printf("%ld %d died\n", time - data->time, data->philo[i].id + 1);
			return (1);
		}
		i++;
	}
	return (0);
}

int	philo_alleat(t_data *data)
{
	int		i;

	i = 0;
	if (data->limit == 0)
		return (0);
	while (i < data->number)
	{
		if (data->philo[i].eat < data->number_eat)
			return (0);
		i++;
	}
	return (1);
}

void	end_game(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number)
	{
		pthread_mutex_unlock(&data->mutex[i]);
		i++;
	}
	i = 0;
	while (i < data->number)
	{
		pthread_join(data->philo[i].thread, NULL);
		i++;
	}
}

void	*master_game(void *arg)
{
	t_data	*data;
	int		i;

	i = 0;
	data = (t_data *)arg;
	while (i < data->number)
	{
		pthread_create(&data->philo[i].thread, NULL, &philo_journey,
			&data->philo[i]);
		i++;
	}
	while (data->end == 0)
	{
		if (philo_death(data) || philo_alleat(data))
			data->end = 1;
	}
	end_game(data);
	return (NULL);
}
