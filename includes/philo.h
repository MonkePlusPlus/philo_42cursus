/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:57:05 by ptheo             #+#    #+#             */
/*   Updated: 2025/01/24 11:41:26 by ptheo            ###   ########.fr       */
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
	long int		time_think;
	long int		start_time;
	long int		time_to_eat;
	long int		time_to_sleep;
	int				max;
	pthread_t		thread;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	var;
	pthread_mutex_t	*text;
}				t_philo;

typedef struct s_data
{
	t_philo			*philo;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	text;
	int				number_philo;
	long int		time_to_die;
	long int		time_to_eat;
	long int		time_to_sleep;
	long int		number_of_time;
}				t_data;

/* DATA */
int			init_data(t_data *data, int ac, char **av);
int			init_philo(t_data *data);
void		free_data(t_data *data);
int			init_mutex(t_data *data);

/* MASTER */
int			check_death(t_data *data);
void		master_thread(t_data *data);

/* PHILO */
void		philo_eating(t_philo *philo);
void		philo_eating_utils(t_philo *philo);
void		philo_sleeping(t_philo *philo);
void		*philo_thread(void *p);
void		stop_thread(t_data *data);

/* UTILS */
int			ft_atoi(const char *nptr);
void		ft_perror(char *str);
int			ft_usleep(size_t milliseconds);
long int	get_current_time(void);
void		message_philo(t_philo *philo, char *message, int end);

#endif