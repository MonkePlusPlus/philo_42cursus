/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:10:20 by ptheo             #+#    #+#             */
/*   Updated: 2024/09/25 17:19:42 by ptheo            ###   ########.fr       */
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
	if (philo->data->limit && philo->eat >= philo->data->number_eat)
	{
		pthread_mutex_lock(&philo->data->eat_all[philo->id]);
		return ;
	}
}

void	is_eating(t_philo *philo)
{
	size_t	time;
	int		right;
	int		id;

	id = philo->id + 1;
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
	printf("%ld %d has taken a fork\n", time - philo->data->time, id);
	if (philo->data->end == 1)
		return ;
	pthread_mutex_lock(&philo->data->mutex[right]);
	if (philo->data->end == 1)
		return ;
	time = get_current_time();
	printf("%ld %d has taken a fork\n", time - philo->data->time, id);
	if (philo->data->end == 0)
		is_eating_utils(philo, right);
}

void	is_sleeping(t_philo *philo)
{
	size_t	time;
	int		id;

	id = philo->id + 1;
	philo->status = SLEEPING;
	time = get_current_time();
	if (philo->data->end == 1)
		return ;
	printf("%ld %d is sleeping\n", time - philo->data->time, id);
	ft_usleep(philo->data->time_sleep);
}

void	is_thinking(t_philo *philo)
{
	int	id;

	id = philo->id + 1;
	philo->time_think = get_current_time();
	philo->status = THINKING;
	if (philo->data->end == 1)
		return ;
	printf("%ld %d is thinking\n", philo->time_think - philo->data->time, id);
}

void	*philo_journey(void *p)
{
	t_philo			*philo;
	int				check;

	philo = (t_philo *)p;
	check = philo->id + philo->data->number;
	while (philo->data->end == 0)
	{
		pthread_mutex_lock(&philo->data->mutex[check]);
		if (philo->data->end == 0)
			is_thinking(philo);
		pthread_mutex_unlock(&philo->data->mutex[check]);
		pthread_mutex_lock(&philo->data->mutex[check]);
		if (philo->data->end == 0)
			is_eating(philo);
		pthread_mutex_unlock(&philo->data->mutex[check]);
		pthread_mutex_lock(&philo->data->mutex[check]);
		if (philo->data->end == 0)
			is_sleeping(philo);
		pthread_mutex_unlock(&philo->data->mutex[check]);
	}
	return (NULL);
}
