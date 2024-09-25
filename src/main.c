/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:56:32 by ptheo             #+#    #+#             */
/*   Updated: 2024/09/25 15:35:09 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
		philo[i].status = THINKING;
		philo[i].data = data;
		philo[i].time_think = get_current_time();
		philo[i].eat = 0;
		if (pthread_mutex_init(&data->mutex[i], NULL) != 0)
			return (NULL);
		if (pthread_mutex_init(&data->mutex[i + data->number], NULL) != 0)
			return (NULL);
		if (pthread_mutex_init(&data->eat_all[i], NULL) != 0)
			return (NULL);
		i++;
	}
	return (philo);
}

int	main(int ac, char **av)
{
	t_data	data;
	int		i;

	i = 0;
	if (ac == 5 || ac == 6)
	{
		init_data(&data);
		if (full_data(&data, ac, av) == -1)
			return (free_data(&data), -1);
		data.time = get_current_time();
		pthread_create(&data.master, NULL, &master_game, &data);
		pthread_join(data.master, NULL);
		free_data(&data);
	}
	else
		return (ft_perror("Error number argument"), -1);
	return (0);
}
