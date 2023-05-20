/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 06:35:59 by lahamoun          #+#    #+#             */
/*   Updated: 2023/05/19 06:35:59 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_info
{
	int				num_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				notefme;
	long			start_time;
	pthread_mutex_t	msg_mutex;
	pthread_mutex_t	mutex;
}			t_info;

typedef struct s_philo
{
	int					id;
	int					num_of_times_eaten;
	long				last_time_ate;
	pthread_t			philo_thread;
	pthread_mutex_t		*left_fork_mutex;
	pthread_mutex_t		*right_fork_mutex;
	struct s_philo		*left;
	struct s_philo		*right;
	pthread_mutex_t		fork;
	struct s_info		*global_info;
}			t_philo;

int		ft_atoi(const char *str);
long	get_time(void);
void	ft_error(char *error_message);
void	ft_usleep(int time);
void	ft_error(char *error_message);
void	*philos_routine(void *t);
int		check_args(int ac, char **av);
int		initilaphilos(t_philo *philos, t_info *global_info);

#endif
