/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lahamoun <lahamoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 07:49:47 by lahamoun          #+#    #+#             */
/*   Updated: 2023/05/20 03:53:29 by lahamoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int ac, char **av)
{
	int	i;
	int	j;

	if (ac < 5 || ac > 6)
	{
		return (ft_error("wrong number of arguments\n"), 1);
	}
	if (ft_atoi(av[2]) <= ft_atoi(av[3]) || ft_atoi(av[2]) <= ft_atoi(av[4]))
	{
		write(2, "Error: TTD should be greater than TTE and TTS\n", 46);
		return (1);
	}
	i = 0;
	while (++i < ac)
	{
		j = 0;
		while (av[i][j] && av[i][j] >= '0' && av[i][j] <= '9')
			j++;
		if (ft_atoi(av[i]) <= 0 || av[i][j])
		{
			write(2, "Error: NOT_eachone(e,s,t)should be greater than 0\n", 50);
			return (1);
		}
	}
	return (0);
}

void	initialize_philo_properties(t_philo *philo, t_info *global_info, int i)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	global_info->start_time = current_time.tv_sec * 1000
		+ current_time.tv_usec / 1000;
	philo->id = i + 1;
	philo->global_info = global_info;
	philo->last_time_ate = global_info->start_time;
	philo->num_of_times_eaten = 0;
	philo->fd = 0;
}

void	initialize_philos(t_philo *philos, t_info *global_info)
{
	int		i;
	t_philo	*tmp;

	i = 0;
	tmp = philos;
	while (i < global_info->num_of_philos)
	{
		initialize_philo_properties(philos, global_info, i);
		if (i < global_info->num_of_philos - 1)
		{
			philos->left = malloc(sizeof(t_philo));
			philos->left->right = philos;
			philos = philos->left;
		}
		else if (i == global_info->num_of_philos - 1)
		{
			tmp->right = philos;
			philos->left = tmp;
		}
		i++;
	}
}
