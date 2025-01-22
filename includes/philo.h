/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: theo <theo@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:57:05 by ptheo             #+#    #+#             */
/*   Updated: 2025/01/22 03:38:02 by theo             ###   ########.fr       */
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
	int				id;
	int				is_alive;
	int				finish;
	struct s_data	*data;
	size_t			time_think;
	size_t			start_time;
	pthread_t		thread;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	var;
}				t_philo;

typedef struct s_data
{
	t_philo			*philo;
	pthread_t		master;
	pthread_mutex_t	*mutex;
	int 			number_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_time;
}				t_data;

/* DATA */
int		init_data(t_data *data, int ac, char **av);
int		init_philo(t_data *data);
void	free_data(t_data *data);

/* MASTER */
int		check_death(t_data *data);
void	*master_thread(void *d);

/* PHILO */
void	philo_eating(t_philo *philo);
void	philo_sleeping(t_philo *philo);
void	*philo_thread(void *p);

/* UTILS */
int		ft_atoi(const char *nptr);
void	ft_perror(char *str);
int		ft_usleep(size_t milliseconds);
size_t	get_current_time(void);

#endif