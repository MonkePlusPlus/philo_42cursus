/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:10:20 by ptheo             #+#    #+#             */
/*   Updated: 2025/01/24 11:37:03 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eating(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->right);
	else
		pthread_mutex_lock(philo->left);
	pthread_mutex_lock(&philo->var);
	if (philo->is_alive == 0)
	{
		if (philo->id % 2 == 0)
			pthread_mutex_unlock(philo->right);
		else
			pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(&philo->var);
		return ;
	}
	pthread_mutex_unlock(&philo->var);
	message_philo(philo, "has taken a fork", 1);
	philo_eating_utils(philo);
}

void	philo_eating_utils(t_philo *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->left);
	else
		pthread_mutex_lock(philo->right);
	pthread_mutex_lock(&philo->var);
	if (philo->is_alive == 0)
	{
		pthread_mutex_unlock(philo->left);
		pthread_mutex_unlock(philo->right);
		pthread_mutex_unlock(&philo->var);
		return ;
	}
	pthread_mutex_unlock(&philo->var);
	message_philo(philo, "has taken a fork", 1);
	pthread_mutex_lock(&philo->var);
	philo->time_think = -1;
	pthread_mutex_unlock(&philo->var);
	message_philo(philo, "is eating", 1);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(philo->right);
}

void	philo_sleeping(t_philo *philo)
{
	pthread_mutex_lock(&philo->var);
	if (philo->is_alive == 0)
	{
		pthread_mutex_unlock(&philo->var);
		return ;
	}
	pthread_mutex_unlock(&philo->var);
	message_philo(philo, "is sleeping", 1);
	ft_usleep(philo->time_to_sleep);
}

int	philo_is_alive(t_philo *philo)
{
	pthread_mutex_lock(&philo->var);
	if (philo->is_alive)
		return (pthread_mutex_unlock(&philo->var), 1);
	else
		return (pthread_mutex_unlock(&philo->var), 0);
}

void	*philo_thread(void *p)
{
	t_philo		*philo;
	long int	nb_eat;

	philo = (t_philo *)p;
	nb_eat = 0;
	while (philo_is_alive(philo))
	{
		message_philo(philo, "is thinking", 1);
		pthread_mutex_lock(&philo->var);
		philo->time_think = get_current_time();
		pthread_mutex_unlock(&philo->var);
		philo_eating(philo);
		nb_eat++;
		pthread_mutex_lock(&philo->var);
		if ((nb_eat >= philo->max && philo->max != -1) || philo->is_alive != 1)
		{
			philo->finish = 1;
			pthread_mutex_unlock(&philo->var);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->var);
		philo_sleeping(philo);
	}
	return (NULL);
}
