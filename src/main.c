/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:56:32 by ptheo             #+#    #+#             */
/*   Updated: 2024/09/20 19:00:38 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

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
		printf("time : %ld\n", data.time);
		while (i < ac - 1)
		{
			pthread_create(&data.philo[i].thread, NULL, philo_journey, &data.philo[i]);
			i++;
		}
		i = 0;
		while (i < ac - 1)
		{
			pthread_join(data.philo[i].thread, NULL);
			i++;
		}
	}
	else
		return (ft_perror("Error number argument"), -1);
	return (0);
}