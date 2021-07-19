/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmisfit <nmisfit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 14:57:18 by nmisfit           #+#    #+#             */
/*   Updated: 2021/07/19 12:07:26 by nmisfit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_all(t_all *all, int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
		return (my_strerror("Error: count of argument"));
	all->number_of_philo = my_atoi(argv[1]);
	all->time_to_die = atoi_time(argv[2]);
	all->time_to_eat = atoi_time(argv[3]);
	all->time_to_sleep = atoi_time(argv[4]);
	all->time_eat_for_die = -1;
	if (argv[5])
		all->time_eat_for_die = my_atoi(argv[5]);
	g_number_of_philo = all->number_of_philo;
	return (1);
}

void	philo_init(int i, t_all *all)
{
	int	left_fork;
	int	right_fork;

	g_philo[i].number = i + 1;
	left_fork = (i + 1) % all->number_of_philo;
	right_fork = i;
	g_philo[i].first_fork = left_fork;
	g_philo[i].second_fork = right_fork;
	if (right_fork < left_fork)
	{
		g_philo[i].first_fork = right_fork;
		g_philo[i].second_fork = left_fork;
	}
	g_philo[i].time_to_die = all->time_to_die;
	g_philo[i].time_to_eat = all->time_to_eat;
	g_philo[i].time_to_sleep = all->time_to_sleep;
	g_philo[i].time_eat_for_die = all->time_eat_for_die;
	g_philo[i].begin_of_starv = -1;
}

int	create_philosophers(t_all *all)
{
	int	i;

	g_philo = (t_philo *)malloc(sizeof(t_philo) * all->number_of_philo);
	g_forks = (t_mutex *)malloc(sizeof(t_mutex) * all->number_of_philo);
	if (!g_philo || !g_forks)
		return (my_strerror("Error: malloc"));
	i = -1;
	while (++i < all->number_of_philo)
		pthread_mutex_init(&g_forks[i], NULL);
	pthread_mutex_init(&g_print, NULL);
	i = -1;
	while (++i < all->number_of_philo)
		philo_init(i, all);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_all	all;

	if (!init_all(&all, argc, argv))
		return (0);
	if (!create_philosophers(&all))
		return (0);
	run_life_of_philosophers();
	return (0);
}
