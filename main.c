/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmisfit <nmisfit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 14:57:18 by nmisfit           #+#    #+#             */
/*   Updated: 2021/07/16 21:36:27 by nmisfit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_all(t_all *all, int argc, char *argv[])
{
	int	i;

	if (argc < 5)
		my_strerror("count of argument");
	//all = (t_all *)malloc(sizeof(t_all *));
	all->number_of_philo = my_atoi(argv[1]);
	all->time_to_die = atoi_time(argv[2]);
	all->time_to_eat = atoi_time(argv[3]);
	all->time_to_sleep = atoi_time(argv[4]);
	all->time_eat_for_die = -1;
	if (argv[5])
		all->time_eat_for_die = my_atoi(argv[5]);
	g_number_of_philo = all->number_of_philo;
}

void	create_philosophers(t_all *all)
{
	philo = (t_philo *)malloc(sizeof(t_philo) * (all->number_of_philo));
	g_forks = (mutex_t *)malloc(sizeof(mutex_t) * all->number_of_philo);
	if (!philo || !g_forks)
		my_strerror("malloc");
	int i = -1;
	while (++i < all->number_of_philo)
		pthread_mutex_init(&g_forks[i], NULL);
	pthread_mutex_init(&g_print, NULL);
	i = -1;
	while (++i < all->number_of_philo)
	{
		philo[i].number = i + 1;
		int index_fork1 = (i + 1) % all->number_of_philo; //left fork
		int index_fork2 = i; //right fork
		
		philo[i].first_fork = index_fork1;
		philo[i].second_fork = index_fork2;
		if (index_fork2 < index_fork1)
		{
			philo[i].first_fork = index_fork2;
			philo[i].second_fork = index_fork1;
		}
		philo[i].time_to_die = all->time_to_die;
		philo[i].time_to_eat = all->time_to_eat;
		philo[i].time_to_sleep = all->time_to_sleep;
		philo[i].time_eat_for_die = all->time_eat_for_die;
		philo[i].begin_of_starv = -1;
	}
}

int	main(int argc, char *argv[])
{
	t_all	all;
	
	init_all(&all, argc, argv);
	create_philosophers(&all);
	run_life_of_philosophers();
	return (0);
}