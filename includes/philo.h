/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:57:05 by ptheo             #+#    #+#             */
/*   Updated: 2024/09/25 15:36:45 by ptheo            ###   ########.fr       */
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
# include <string.h>
# include <pthread.h>
# include <sys/time.h>

# define THINKING 1
# define EATING 2
# define DEATH 3
# define SLEEPING 4

typedef struct s_philo
{
	pthread_t		thread;
	struct s_data	*data;
	size_t			time_think;
	int				id;
	int				status;
	int				eat;
}				t_philo;

typedef struct s_data
{
	pthread_t		master;
	t_philo			*philo;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*eat_all;
	size_t			time;
	size_t			time_die;
	size_t			time_eat;
	size_t			time_sleep;
	size_t			number_eat;
	int				end;
	int				limit;
	int				number;
}				t_data;

/* DATA */
int		init_data(t_data *data);
int		full_data(t_data *data, int ac, char **av);
void	free_data(t_data *data);
void	print_data(t_data *data);

/* MASTER */
void	*master_game(void *arg);
int		philo_death(t_data *data);
int		philo_alleat(t_data *data);

/* PHILO */
t_philo	*init_philo(t_data *data, int number);
void	*philo_journey(void *arg);
void	is_eating_utils(t_philo *philo, int right);
void	is_eating(t_philo *philo);
void	is_sleeping(t_philo *philo);
void	is_thinking(t_philo *philo);

/* UTILS */
int		ft_atoi(const char *nptr);
void	ft_perror(char *str);
int		ft_usleep(size_t milliseconds);
size_t	get_current_time(void);

#endif