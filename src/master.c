/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 21:31:32 by ptheo             #+#    #+#             */
/*   Updated: 2024/09/25 16:06:32 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	philo_death(t_data *data)
{
	size_t	time;
	int		i;
	int		p;

	i = 0;
	p = 0;
	time = get_current_time();
	while (i < data->number)
	{
		if (data->philo[i].status == THINKING
			&& (time - data->philo[i].time_think) >= data->time_die)
		{
			p = i;
			i = data->number;
			while (i < data->number * 2)
			{
				pthread_mutex_unlock(&data->mutex[i]);
				pthread_mutex_lock(&data->mutex[i]);
				i++;
			}
			printf("%ld %d died\n", time - data->time, p + 1);
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

/*
	i = data->number;
	while (i < data->number * 2)
	{
		pthread_mutex_lock(&data->mutex[i]);
		i++;
	}*/
	i = 0;
	while (i < data->number * 2)
	{
		if (i < data->number)
			pthread_mutex_unlock(&data->eat_all[i]);
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
		pthread_mutex_lock(&data->eat_all[i]);
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
