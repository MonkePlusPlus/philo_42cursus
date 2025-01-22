/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 21:31:32 by ptheo             #+#    #+#             */
/*   Updated: 2025/01/22 04:37:22 by theo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_death(t_data *data)
{
	int		i;
	size_t	time;

	i = 0;
	while (i < data->number_philo)
	{
		pthread_mutex_lock(&data->philo[i].var);
		time = data->philo[i].time_think;
		pthread_mutex_unlock(&data->philo[i].var);
		if (get_current_time() - time >= data->time_to_die && time != -1)
		{
			printf("%ld %d died\n", get_current_time() - data->philo[i].start_time, i);
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_nb_eat(t_data *data)
{
	int		i;
	int		check;

	i = 0;
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

void	*master_thread(void *d)
{
	int		end;
	int		i;
	t_data	*data;

	end = 1;
	data = (t_data *)d;
	while (end)
	{
		if (check_death(data) || check_nb_eat(data))
		{
			i = 0;
			while (i < data->number_philo)
			{
				data->philo[i].is_alive = 0;
				i++;
			}
			free_data(data);
			end = 0;
		}
	}
	return (NULL);
}