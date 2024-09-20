/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:56:32 by ptheo             #+#    #+#             */
/*   Updated: 2024/09/20 21:51:43 by ptheo            ###   ########.fr       */
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
		pthread_create(&data.master, NULL, &master_game, &data);
		pthread_join(data.master, NULL);
		free_data(&data);
	}
	else
		return (ft_perror("Error number argument"), -1);
	return (0);
}