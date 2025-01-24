/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 21:31:32 by ptheo             #+#    #+#             */
/*   Updated: 2025/01/24 11:35:39 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_death(t_data *data)
{
	int			i;
	long int	time;

	i = 0;
	time = 0;
	while (i < data->number_philo)
	{
		pthread_mutex_lock(&data->philo[i].var);
		time = data->philo[i].time_think;
		if (get_current_time() - time >= data->time_to_die && time != -1)
		{
			pthread_mutex_unlock(&data->philo[i].var);
			message_philo(&data->philo[i], "died", 0);
			return (1);
		}
		pthread_mutex_unlock(&data->philo[i].var);
		i++;
	}
	return (0);
}

int	check_nb_eat(t_data *data)
{
	int		i;
	int		check;

	i = 0;
	check = 0;
	while (i < data->number_philo)
	{
		pthread_mutex_lock(&data->philo[i].var);
		check = data->philo[i].finish;
		pthread_mutex_unlock(&data->philo[i].var);
		if (!check)
			return (0);
		i++;
	}
	return (1);
}

void	master_thread(t_data *data)
{
	int		end;
	int		i;

	end = 1;
	while (end != 0)
	{
		if (check_death(data) || check_nb_eat(data))
		{
			i = 0;
			while (i < data->number_philo)
			{
				pthread_mutex_lock(&data->philo[i].var);
				data->philo[i].is_alive = 0;
				pthread_mutex_unlock(&data->philo[i].var);
				i++;
			}
			end = 0;
			return ;
		}
	}
}
