/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:10:20 by ptheo             #+#    #+#             */
/*   Updated: 2024/09/22 18:50:40 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	is_eating_utils(t_philo *philo, int right)
{
	size_t	time;

	time = get_current_time();
	if (philo->data->end == 1)
		return ;
	philo->status = EATING;
	printf("%ld %d is eating\n", time - philo->data->time, philo->id + 1);
	philo->eat += 1;
	ft_usleep(philo->data->time_eat);
	pthread_mutex_unlock(&philo->data->mutex[philo->id]);
	pthread_mutex_unlock(&philo->data->mutex[right]);
}

void	is_eating(t_philo *philo)
{
	size_t	time;
	int		right;

	if (philo->id == philo->data->number - 1)
		right = 0;
	else
		right = philo->id + 1;
	if (philo->data->end == 1)
		return ;
	pthread_mutex_lock(&philo->data->mutex[philo->id]);
	if (philo->data->end == 1)
		return ;
	time = get_current_time();
	printf("%ld %d has taken a fork\n", time - philo->data->time, philo->id + 1);
	if (philo->data->end == 1)
		return ;
	pthread_mutex_lock(&philo->data->mutex[right]);
	if (philo->data->end == 1)
		return ;
	time = get_current_time();
	printf("%ld %d has taken a fork\n", time - philo->data->time, philo->id + 1);
	if (philo->data->end == 0)
		is_eating_utils(philo, right);
}

void	is_sleeping(t_philo *philo)
{
	size_t	time;

	philo->status = SLEEPING;
	time = get_current_time();
	if (philo->data->end == 1)
		return ;
	printf("%ld %d is sleeping\n", time - philo->data->time, philo->id + 1);
	ft_usleep(philo->data->time_sleep);
}

void	is_thinking(t_philo *philo)
{
	philo->status = THINKING;
	philo->time_think = get_current_time();
	if (philo->data->end == 1)
		return ;
	printf("%ld %d is thinking\n", philo->time_think - philo->data->time,
		philo->id + 1);
}

void	*philo_journey(void *p)
{
	t_philo			*philo;
	int				right;

	philo = (t_philo *)p;
	philo->time_think = get_current_time();
	printf("%ld %d is thinking\n", philo->time_think - philo->data->time,
		philo->id + 1);
	while (philo->data->end == 0)
	{
		if (philo->data->end == 0)
			is_eating(philo);
		if (philo->data->end == 0)
			is_sleeping(philo);
		if (philo->data->end == 0)
			is_thinking(philo);
	}
	return (NULL);
}
