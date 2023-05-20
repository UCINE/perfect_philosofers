/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 04:14:07 by lahamoun          #+#    #+#             */
/*   Updated: 2023/05/19 06:24:35 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Function 1: Initialization
int	init_main(int ac, char **av, t_philo **philos, t_info **global_info)
{
	int	num_of_philos;

	if (check_args(ac, av))
		return (1);
	num_of_philos = ft_atoi(av[1]);
	*philos = malloc(sizeof(t_philo));
	*global_info = malloc(sizeof(t_info));
	if (!*philos || !*global_info)
		return (1);
	(*global_info)->num_of_philos = num_of_philos;
	(*global_info)->time_to_die = ft_atoi(av[2]);
	(*global_info)->time_to_eat = ft_atoi(av[3]);
	(*global_info)->time_to_sleep = ft_atoi(av[4]);
	if (pthread_mutex_init(&(*global_info)->mutex, NULL) != 0)
		return (ft_error("Mutex initialization failed"), 1);
	return (0);
}

// Function 2: Further Initialization and Thread Creation
int	create_threads(char **av, t_philo *philos, t_info *global_info,
pthread_t **thread)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&global_info->msg_mutex, NULL) != 0)
		return (ft_error("Thread creation failed"), 1);
	global_info->notefme = -42;
	*thread = malloc(sizeof(pthread_t) * global_info->num_of_philos);
	if (av[5])
		global_info->notefme = ft_atoi(av[5]);
	initilaphilos(philos, global_info);
	while (i < global_info->num_of_philos)
	{
		if (pthread_create(&(*thread)[i], NULL, &philos_routine, philos) != 0)
			return (ft_error("Thread creation failed"), 1);
		pthread_detach((*thread)[i]);
		philos = philos->left;
		i++;
	}
	return (0);
}

int	check_and_print_status(t_philo *philos, t_info *global_info, int *eat)
{
	pthread_mutex_lock(&philos->global_info->mutex);
	if (philos->num_of_times_eaten == global_info->notefme)
		(*eat)++;
	if (get_time() - philos->last_time_ate > global_info->time_to_die)
	{
		pthread_mutex_lock(&philos->global_info->msg_mutex);
		printf("%ld philo %d is dead\n", get_time()
			- philos->global_info->start_time, philos->id);
		return (0);
	}
	pthread_mutex_unlock(&philos->global_info->mutex);
	philos = philos->left;
	return (1);
}

int	main_loop(t_philo *philos, t_info *global_info)
{
	int	i;
	int	eat;

	eat = 0;
	while (1)
	{
		i = 0;
		eat = 0;
		while (i < global_info->num_of_philos)
		{
			if (!check_and_print_status(philos, global_info, &eat))
				return (0);
			i++;
		}
		if (eat == global_info->num_of_philos)
		{
			pthread_mutex_lock(&philos->global_info->msg_mutex);
			return (0);
		}
		usleep(1000);
	}
	return (0);
}

// Main function
int	main(int ac, char **av)
{
	t_philo		*philos;
	t_info		*global_info;
	pthread_t	*thread;

	if (init_main(ac, av, &philos, &global_info))
		return (1);
	create_threads(av, philos, global_info, &thread);
	return (main_loop(philos, global_info));
}
