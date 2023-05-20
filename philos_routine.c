/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 03:36:37 by lahamoun          #+#    #+#             */
/*   Updated: 2023/05/20 04:31:58 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	c;

	gettimeofday(&c, NULL);
	return (c.tv_sec * 1000 + c.tv_usec / 1000);
}

void	ft_usleep(int time)
{
	long	c;

	c = get_time();
	while (get_time() - c < time)
	{
		usleep(100);
	}
}

void	philosopher_eating(t_philo *philos)
{
	pthread_mutex_lock(&philos->fork);
	pthread_mutex_lock(&philos->left->fork);
	pthread_mutex_lock(&philos->global_info->msg_mutex);
	pthread_mutex_lock(&philos->global_info->mutex);
	philos->last_time_ate = get_time();
	pthread_mutex_unlock(&philos->global_info->mutex);
	printf("%ld philo %d has taken forks\n", get_time()
		- philos->global_info->start_time, philos->id);
	printf("%ld philo %d is eating\n", get_time()
		- philos->global_info->start_time, philos->id);
	pthread_mutex_unlock(&philos->global_info->msg_mutex);
	ft_usleep(philos->global_info->time_to_eat);
	pthread_mutex_unlock(&philos->left->fork);
	pthread_mutex_unlock(&philos->fork);
	pthread_mutex_lock(&philos->global_info->mutex);
	if (++philos->num_of_times_eaten == philos->global_info->notefme)
	{
		pthread_mutex_unlock(&philos->global_info->mutex);
		return ;
	}
	pthread_mutex_unlock(&philos->global_info->mutex);
}

void	philosopher_sleeping_thinking(t_philo *philos)
{
	pthread_mutex_lock(&philos->global_info->msg_mutex);
	printf("%ld philo %d is sleeping\n", get_time()
		- philos->global_info->start_time, philos->id);
	pthread_mutex_unlock(&philos->global_info->msg_mutex);
	ft_usleep(philos->global_info->time_to_sleep);
	pthread_mutex_lock(&philos->global_info->msg_mutex);
	printf("%ld philo %d is thinking\n", get_time()
		- philos->global_info->start_time, philos->id);
	pthread_mutex_unlock(&philos->global_info->msg_mutex);
}

void	*philos_routine(void *t)
{
	t_philo	*philos;

	philos = (t_philo *)t;
	if (philos->id % 2 == 0)
		usleep(1000);
	while (1)
	{
		philosopher_eating(philos);
		philosopher_sleeping_thinking(philos);
	}
}
