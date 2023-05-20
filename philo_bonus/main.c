/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 04:14:07 by lahamoun          #+#    #+#             */
/*   Updated: 2023/05/20 03:20:46 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_dead(t_philo *philos)
{
	while (1)
	{
		if (get_time()
			- philos->last_time_ate > philos->global_info->time_to_die)
		{
			sem_wait(philos->global_info->msg_sem);
			printf("%ldphilo %d is dead\n", get_time()
				- philos->global_info->start_time, philos->id);
			exit(1);
		}
		usleep(100);
	}
}

void	wait_philo(t_philo *philos)
{
	int	s;
	int	i;

	i = 0;
	while (wait(&s) != -1)
	{
		if (WEXITSTATUS(s))
		{
			while (i < philos->global_info->num_of_philos)
			{
				kill(philos->fd, SIGKILL);
				philos = philos->left;
				i++;
			}
			exit(0);
		}
	}
}

void	create_p(t_philo *philos)
{
	int			i;
	pthread_t	p;

	i = 0;
	while (i < philos->global_info->num_of_philos)
	{
		philos->fd = fork();
		if (philos->fd == -1)
			ft_error("fork failed");
		if (philos->fd == 0)
		{
			pthread_create(&p, NULL, philosopher_routine, philos);
			if (philos->id % 2 == 0)
				usleep(3000 * 1000);
			check_dead(philos);
			exit(0);
		}
		else
			philos = philos->left;
		i++;
	}
}

void	initialize(int ac, char **av, t_philo **philos, t_info **global_info)
{
	int		num_of_philos;

	num_of_philos = ft_atoi(av[1]);
	*philos = malloc(sizeof(t_philo) * num_of_philos);
	*global_info = malloc(sizeof(t_info));
	(*global_info)->num_of_philos = num_of_philos;
	(*global_info)->time_to_die = ft_atoi(av[2]);
	(*global_info)->time_to_eat = ft_atoi(av[3]);
	(*global_info)->time_to_sleep = ft_atoi(av[4]);
	(*philos)->global_info = *global_info;
	(*philos)->global_info->msg_lock = sem_open("/msg_lock", O_CREAT, 0644, 1);
	if ((*philos)->global_info->msg_lock == SEM_FAILED)
		ft_error("semaphore initialization failed");
	(*philos)->global_info->msg_sem = sem_open("/msg_sem", O_CREAT, 0644, 1);
	if ((*philos)->global_info->msg_sem == SEM_FAILED)
		ft_error("semaphore initialization failed");
	(*philos)->global_info->forks = sem_open("/my_forks", O_CREAT, 0644,
			num_of_philos);
	if ((*philos)->global_info->msg_lock == SEM_FAILED)
		ft_error("semaphore initialization failed");
	(*global_info)->notefme = -42;
	if (ac == 6)
		(*global_info)->notefme = ft_atoi(av[5]);
}

int	main(int ac, char **av)
{
	t_philo	*philos;
	t_info	*global_info;
	int		i;

	i = 0;
	if (check_args(ac, av))
		return (1);
	sem_unlink("/msg_lock");
	sem_unlink("/msg_sem");
	sem_unlink("/my_forks");
	initialize(ac, av, &philos, &global_info);
	if (!philos || !global_info)
		return (1);
	initialize_philos(philos, global_info);
	create_p(philos);
	wait_philo(philos);
	return (0);
}
