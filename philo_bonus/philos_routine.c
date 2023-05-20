/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 07:58:45 by lahamoun          #+#    #+#             */
/*   Updated: 2023/05/20 03:56:33 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	get_time(void)
{
	struct timeval	c;

	gettimeofday(&c, NULL);
	return (c.tv_sec * 1000 + c.tv_usec / 1000);
}

void	ft_usleep(unsigned long time)
{
	unsigned long	c;

	c = get_time();
	while (get_time() - c < time)
	{
		usleep(300);
	}
}

void	philosopher_eating(t_philo *philo)
{
	sem_wait(philo->global_info->forks);
	sem_wait(philo->global_info->forks);
	sem_wait(philo->global_info->msg_sem);
	printf("%ld philo %d has taken a fork\n", get_time()
		- philo->global_info->start_time, philo->id);
	sem_post(philo->global_info->msg_sem);
	philo->last_time_ate = get_time();
	sem_wait(philo->global_info->msg_sem);
	printf("%ld philo %d is eating\n", get_time()
		- philo->global_info->start_time, philo->id);
	sem_post(philo->global_info->msg_sem);
	ft_usleep(philo->global_info->time_to_eat);
	sem_post(philo->global_info->forks);
	sem_post(philo->global_info->forks);
	if (++philo->num_of_times_eaten == philo->global_info->notefme)
		exit(0);
}

void	philosopher_sleeping_thinking(t_philo *philo)
{
	sem_wait(philo->global_info->msg_sem);
	printf("%ld philo %d is sleeping\n", get_time()
		- philo->global_info->start_time, philo->id);
	sem_post(philo->global_info->msg_sem);
	ft_usleep(philo->global_info->time_to_sleep);
	sem_wait(philo->global_info->msg_sem);
	printf("%ld philo %d is thinking\n", get_time()
		- philo->global_info->start_time, philo->id);
	sem_post(philo->global_info->msg_sem);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (1)
	{
		philosopher_eating(philo);
		philosopher_sleeping_thinking(philo);
	}
	exit(0);
}
