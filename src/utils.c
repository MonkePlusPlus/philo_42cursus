/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 18:14:19 by ptheo             #+#    #+#             */
/*   Updated: 2024/09/18 20:01:03 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	ft_perror(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
	write(2, "\n", 1);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	result;

	i = 0;
	result = 0;
    while (nptr[i])
    {
        if (!(nptr[i] >= '0' && nptr[i] <= '9'))
            return (-1);
        i++;
    }
    i = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result);
}
