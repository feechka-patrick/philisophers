/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmisfit <nmisfit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 14:57:18 by nmisfit           #+#    #+#             */
/*   Updated: 2021/07/15 17:29:56 by nmisfit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	my_strerror(char *message)
{
	printf("%s %s\n", "Error: ", message);
	exit(1);
}

void	init_all(t_all *all, int argc, char *argv[])
{
	int	i;

	if (argc < 5)
		my_strerror("count of argument\n");
	all->number_of_philo = atoi_time(argv[1]);
	all->time_to_die = atoi_time(argv[2]);
	all->time_to_eat = atoi_time(argv[3]);
	all->time_to_sleep = atoi_time(argv[4]);
	all->n_eat = (int *)malloc(sizeof(int) * (argc - 5));
	if (!(all->n_eat))
		my_strerror("malloc\n");
	i = 4;
	while(argv[++i])
		all->n_eat[i] = my_atoi(argv[i]);
}

void	create_philosophers(t_all	*all)
{
	t_philo	*philo;

	philo = (t_philo *)malloc(sizeof(t_philo) * all->number_of_philo);
	g_forks = (mutex_t *)malloc(sizeof(mutex_t) * all->number_of_philo);
	if (!philo || !g_forks)
		my_strerror("malloc\n");
	int i = -1;
	while (++i < all->number_of_philo)
	{
		philo[i].number = i + 1;
		int index_fork1 = (i + 1) % all->number_of_philo; //left fork
		int index_fork2 = i; //right fork
		if (index_fork2 < index_fork1)
		{
			philo[i].first_fork = g_forks[index_fork2];
			philo[i].second_fork = g_forks[index_fork1];
		}
		else
		{
			philo[i].first_fork = g_forks[index_fork1];
			philo[i].second_fork = g_forks[index_fork2];
		}
	}
}

int	main(int argc, char *argv[])
{
	t_all	*all;
	
	init_all(all, argc, argv);
	create_philosophers(all);
	
}