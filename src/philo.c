/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:10:20 by ptheo             #+#    #+#             */
/*   Updated: 2025/01/23 17:59:50 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	philo_eating(t_philo *philo)
{
	pthread_mutex_lock(philo->right);

	pthread_mutex_lock(&philo->var);
	if (philo->is_alive == 0)
	{
		pthread_mutex_unlock(&philo->var);
		return ;
	}
	pthread_mutex_unlock(&philo->var);

	printf("%ld %d has taken a fork\n", get_current_time() - philo->start_time, philo->id);
	pthread_mutex_lock(philo->left);

	pthread_mutex_lock(&philo->var);
	if (philo->is_alive == 0)
	{
		pthread_mutex_unlock(&philo->var);
		return ;
	}
	pthread_mutex_unlock(&philo->var);

	printf("%ld %d has taken a fork\n", get_current_time() - philo->start_time, philo->id);

	pthread_mutex_lock(&philo->var);
	philo->time_think = -1;
	printf("%ld %d is eating\n", get_current_time() - philo->start_time, philo->id);
	pthread_mutex_unlock(&philo->var);

	ft_usleep(philo->data->time_to_eat);
	
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
	
	printf("%ld %d is sleeping\n", get_current_time() - philo->start_time, philo->id);
	ft_usleep(philo->data->time_to_sleep);
}

void	*philo_thread(void *p)
{
	t_philo	*philo;
	int		nb_eat;

	philo = (t_philo *)p;
	nb_eat = 0;
	philo->is_alive = 1;
	while (philo->is_alive == 1)
	{
		printf("%ld %d is thinking\n", get_current_time() - philo->start_time,
				philo->id);

		pthread_mutex_lock(&philo->var);
		philo->time_think = get_current_time();
		pthread_mutex_unlock(&philo->var);
		
		philo_eating(philo);
		nb_eat++;

		pthread_mutex_lock(&philo->var);
		if ((nb_eat >= philo->data->number_of_time && philo->data->number_of_time != -1) || philo->is_alive != 1)
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
