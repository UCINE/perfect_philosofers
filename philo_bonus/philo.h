/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+        
	+:+     */
/*   By: lahamoun <lahamoun@student.42.fr>          +#+  +:+      
	+#+        */
/*                                                +#+#+#+#+#+  
	+#+           */
/*   Created: 2023/03/08 04:14:29 by lahamoun          #+#    #+#             */
/*   Updated: 2023/03/08 04:14:29 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_info
{
	int				num_of_philos;
	int				notefme;
	int				number_eat;
	unsigned long	time_to_die;
	unsigned long	time_to_eat;
	unsigned long	time_to_sleep;
	unsigned long	start_time;
	sem_t			*msg_sem;
	pthread_mutex_t	msg_mutex;
	sem_t			*msg_lock;
	pthread_mutex_t	mutex;
	sem_t			*forks;
}			t_info;

typedef struct s_philo
{
	int				id;
	int				num_of_times_eaten;
	int				fd;
	unsigned long	last_time_ate;
	pthread_t		philo_thread;
	struct s_philo	*left;
	struct s_philo	*right;
	t_info			*global_info;
	pthread_t		*thread;
}			t_philo;

void			check_dead(t_philo *philos);
int				ft_atoi(const char *str);
void			ft_error(char *error_message);
int				check_args(int ac, char **av);
void			initialize_philos(t_philo *philos, t_info *global_info);
unsigned long	get_time(void);
void			ft_usleep(unsigned long time);
void			check_dead(t_philo *philos);
void			*philosopher_routine(void *arg);
void			create_p(t_philo *philos);

#endif
