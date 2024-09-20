/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:10:20 by ptheo             #+#    #+#             */
/*   Updated: 2024/09/20 19:02:02 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	*philo_journey(void *p)
{
	size_t	time;
	t_philo			*philo;
	int				right;

	philo = (t_philo *)p;
	if (philo->id == philo->data->number - 1)
		right = 0;
	else
		right = philo->id + 1;
	while (philo->data->end == 0)
	{
		pthread_mutex_lock(&philo->data->mutex[philo->id]);
		pthread_mutex_lock(&philo->data->mutex[right]);
		time = get_current_time();
		printf("%ld : %d has taken a fork\n", time - philo->data->time, philo->id + 1);
		time = get_current_time();
		printf("%ld : %d is eating\n", time - philo->data->time, philo->id + 1);
		usleep(philo->data->time_eat);
		philo->status = EATING;
		pthread_mutex_unlock(&philo->data->mutex[philo->id]);
		pthread_mutex_unlock(&philo->data->mutex[right]);
		if (philo->status == EATING)
		{
			time = get_current_time();
			printf("%ld : %d is sleeping\n", time - philo->data->time, philo->id + 1);
			usleep(philo->data->time_sleep);
			philo->status = 0;
		}
		else if (philo->status == 0)
		{
			philo->time_think = get_current_time();
			printf("%ld : %d is thinking\n", philo->time_think - philo->data->time, philo->id + 1);
		}
		time = get_current_time();
		if (time - philo->time_think > philo->data->time_die)
		{
			printf("%ld : %d died\n", time - philo->data->time, philo->id + 1);
			pthread_mutex_lock(&philo->data->mutex[philo->data->number]);
			philo->data->end = 1;
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
		philo[i].status = 0;
		philo[i].data = data;
		if (pthread_mutex_init(&data->mutex[i], NULL) != 0)
			return (NULL);
		i++;
	}
	return (philo);
}