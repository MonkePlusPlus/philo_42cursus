/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:57:05 by ptheo             #+#    #+#             */
/*   Updated: 2024/09/18 21:46:17 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <stdarg.h>
# include <stdint.h>
# include <pthread.h>
# include <sys/time.h>

# define THINKING 1
# define EATING 2
# define DEATH 3

typedef	struct s_philo
{
	pthread_t		thread;
	struct s_data	*data;
	struct timeval	time_think;
	int				id;
	int				status;
	int				fork;
}				t_philo;

typedef struct s_data
{
	t_philo			*philo;
	pthread_mutex_t mutex;
	struct timeval	time;
	int				end;
	int				number;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				time_number;
}				t_data;

/* DATA */
int		init_data(t_data *data);
int		full_data(t_data *data, int ac, char **av);
void	free_data(t_data *data);
void    print_data(t_data *data);

/* PHILO */
t_philo	*init_philo(t_data *data, int number);
void	*philo_journey(void *arg);

/* UTILS */
int		ft_atoi(const char *nptr);
void	ft_perror(char *str);

#endif