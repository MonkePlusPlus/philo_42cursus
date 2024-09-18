/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:10:20 by ptheo             #+#    #+#             */
/*   Updated: 2024/09/19 00:18:35 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*philo_journey(void *p)
{
	struct timeval	time;
	t_philo			*philo;
	int				right;

	philo = (t_philo *)p;
	if (philo->id == philo->data->number)
		right = 0;
	else
		right = philo->id + 1;
	while (philo->data->end != 1)
	{
		if (philo->fork && philo->data->philo[right].fork && philo->data->end != 1)
		{
			philo->fork = 0;
			philo->data->philo[right].fork = 0;
			gettimeofday(&time, NULL);
			if (philo->data->end != 1)
				printf("%ld %d has taken a fork\n", time.tv_usec - philo->data->time.tv_usec, philo->id + 1);
			gettimeofday(&time, NULL);
			if (philo->data->end != 1)
				printf("%ld %d is eating\n", time.tv_usec - philo->data->time.tv_usec, philo->id + 1);
			usleep(philo->data->time_eat);
			philo->data->philo[right].fork = 1;
			philo->fork = 1;
			gettimeofday(&time, NULL);
			if (philo->data->end != 1)
				printf("%ld %d is sleeping\n", time.tv_usec - philo->data->time.tv_usec, philo->id + 1);
			usleep(philo->data->time_sleep);
			philo->status = 0;
		}
		else if (philo->status != THINKING && philo->data->end != 1)
		{
			gettimeofday(&philo->time_think, NULL);
			if (philo->data->end != 1)
				printf("%ld %d is thinking\n", philo->time_think.tv_usec - philo->data->time.tv_usec, philo->id + 1);
			philo->status = THINKING;
		}
		else if (philo->data->end != 1)
		{
			gettimeofday(&time, NULL);
			if (time.tv_usec - philo->time_think.tv_usec > philo->data->time_die)
			{
				if (philo->data->end != 1)
					printf("%ld %d died\n", time.tv_usec - philo->data->time.tv_usec, philo->id + 1);
				philo->data->end = 1;
				return (NULL);
			}
		}
	}
	return (NULL);
}

t_philo	*init_philo(t_data *data, int number)
{
	t_philo	*philo;
	int		i;

	i = 0;
	philo = (t_philo *)malloc(sizeof(t_philo) * number);
	if (philo == NULL)
		return (ft_perror("Error malloc: init_philo()"), NULL);
	while (i < number)
	{
		philo[i].id = i;
		philo[i].fork = 1;
		philo[i].status = 0;
		philo[i].data = data;
		i++;
	}
	return (philo);
}