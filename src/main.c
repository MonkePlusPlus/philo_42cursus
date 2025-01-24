/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:56:32 by ptheo             #+#    #+#             */
/*   Updated: 2025/01/24 20:05:03 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		if (init_data(&data, ac, av) == -1)
			return (free_data(&data), -1);
		if (data.number_philo > 1)
			start_philo(&data);
		else if (data.number_philo < 1)
			return (-1);
		else
			one_philo(&data);
		free_data(&data);
	}
	else
		return (ft_perror("Error number argument"), -1);
	return (0);
}
