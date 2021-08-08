/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmisfit <nmisfit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 14:57:18 by nmisfit           #+#    #+#             */
/*   Updated: 2021/08/03 11:34:58 by nmisfit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_all(t_all *all, int argc, char *argv[])
{
	if (argc != 5 && argc != 6)
		return (my_strerror("Error: count of argument", NULL));
	all->number_of_philo = my_atoi(argv[1]);
	all->time_to_die = atoi_time(argv[2]);
	all->time_to_eat = atoi_time(argv[3]);
	all->time_to_sleep = atoi_time(argv[4]);
	all->time_eat_for_die = -1;
	if (argv[5])
	{
		all->time_eat_for_die = my_atoi(argv[5]);
		if (all->time_eat_for_die == -1)
			return (my_strerror("Error: invalid argument", NULL));
	}
	if (all->number_of_philo == -1 || all->time_to_die == -1
		|| all->time_to_eat == -1 || all->time_to_sleep == -1)
		return (my_strerror("Error: invalid argument", NULL));
	return (1);
}

void	philo_init(int i, t_all *all, t_philo *philo, t_global *info)
{
	int	left_fork;
	int	right_fork;

	philo->number = i + 1;
	left_fork = (i + 1) % all->number_of_philo;
	right_fork = i;
	philo->first_fork = &info->forks[left_fork];
	philo->second_fork = &info->forks[right_fork];
	philo->time_to_die = all->time_to_die;
	philo->time_to_eat = all->time_to_eat;
	philo->time_to_sleep = all->time_to_sleep;
	philo->time_eat_for_die = all->time_eat_for_die;
	philo->begin_of_starv = -1;
}

int	create_philosophers(t_all *all, t_global *info)
{
	int	i;

	info->philo = (t_philo *)malloc(sizeof(t_philo) * all->number_of_philo);
	info->forks = (t_mutex *)malloc(sizeof(t_mutex) * all->number_of_philo);
	if (!info->philo || !info->forks)
		return (my_strerror("Error: malloc", info));
	i = -1;
	while (++i < all->number_of_philo)
		pthread_mutex_init(&info->forks[i], NULL);
	info->print = (t_mutex *)malloc(sizeof(t_mutex));
	pthread_mutex_init(info->print, NULL);
	i = -1;
	while (++i < all->number_of_philo)
	{
		philo_init(i, all, &info->philo[i], info);
		info->philo[i].print = info->print;
	}
	return (1);
}

int	main(int argc, char *argv[])
{
	t_all		all;
	t_global	info;

	if (!init_all(&all, argc, argv))
		return (0);
	info.number_of_philo = all.number_of_philo;
	if (!create_philosophers(&all, &info))
		return (0);
	run_life_of_philosophers(&info);
	return (0);
}
