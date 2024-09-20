/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:10:20 by ptheo             #+#    #+#             */
/*   Updated: 2024/09/20 21:51:09 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	is_eating(t_philo *philo)
{
	size_t	time;
	int		right;

	if (philo->id == philo->data->number - 1)
		right = 0;
	else
		right = philo->id + 1;
	pthread_mutex_lock(&philo->data->mutex[philo->id]);
	time = get_current_time();
	printf("%ld : %d has taken a fork\n", time - philo->data->time, philo->id + 1);
	pthread_mutex_lock(&philo->data->mutex[right]);
	time = get_current_time();
	printf("%ld : %d has taken a fork\n", time - philo->data->time, philo->id + 1);
	philo->status = EATING;
	time = get_current_time();
	printf("%ld : %d is eating\n", time - philo->data->time, philo->id + 1);
	ft_usleep(philo->data->time_eat);
	pthread_mutex_unlock(&philo->data->mutex[philo->id]);
	pthread_mutex_unlock(&philo->data->mutex[right]);
	philo->status = SLEEPING;
}

void	is_sleeping(t_philo *philo)
{
	size_t	time;

	time = get_current_time();
	printf("%ld : %d is sleeping\n", time - philo->data->time, philo->id + 1);
	ft_usleep(philo->data->time_sleep);
	philo->status = THINKING;	
}

void	is_thinking(t_philo *philo)
{
	philo->time_think = get_current_time();
	printf("%ld : %d is thinking\n", philo->time_think - philo->data->time, philo->id + 1);
}

void	*philo_journey(void *p)
{
	size_t	time;
	t_philo			*philo;
	int				right;

	philo = (t_philo *)p;
	philo->status = THINKING;
	philo->time_think = get_current_time();
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