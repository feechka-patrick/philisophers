/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_of_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmisfit <nmisfit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 16:33:40 by nmisfit           #+#    #+#             */
/*   Updated: 2021/07/16 21:55:17 by nmisfit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

mls_t	get_current_time(void)
{
	struct timeval	current_time;
	mls_t	timestamp; //milliseconds

	gettimeofday(&current_time, NULL);	
	timestamp = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (timestamp);
}

void	do_timestamp(char *activity, int X)
{
	mls_t	timestamp; //milliseconds
	
	timestamp = get_current_time() - g_time_of_begin;
	pthread_mutex_lock(&g_print);
	printf("%ld: number %d %s\n", timestamp, X, activity);
	pthread_mutex_unlock(&g_print);
}

void	*check_death(void *ptr)
{
	int	i;
	mls_t	time_of_starv;

	while (1)
	{
		i = -1;
		while (++i < g_number_of_philo)
		{
			time_of_starv = 0;
			if (philo[i].begin_of_starv != -1)
			{
				time_of_starv = get_current_time() - philo[i].begin_of_starv;
				if (philo[i].begin_of_starv != -1 && time_of_starv >= philo[i].time_to_die)
				{
					mls_t	timestamp = get_current_time() - g_time_of_begin;
					// //
					// pthread_mutex_lock(&g_print);
					// printf("--> time_of_starv: %ld, time_to_die: %ld\n", time_of_starv, philo[i].time_to_die);
					// printf("--> begin_of_starv: %ld\n", philo[i].begin_of_starv);
					// pthread_mutex_unlock(&g_print);
					// //
					pthread_mutex_lock(&g_print);
					printf("%ld: number %d %s\n", timestamp, i + 1, "died");
					//free
					exit(1); //заменить
				}
			}
		}
	}
}

void	*begin_amazing_life(void *ptr)
{
	int i = *(int *)ptr - 1;
	philo[i].begin_of_starv = get_current_time();	
	while (1)
	{
		pthread_mutex_lock(&(g_forks[philo[i].first_fork]));
		do_timestamp("has taken a fork", philo[i].number);
		pthread_mutex_lock(&(g_forks[philo[i].second_fork]));
		do_timestamp("has taken a fork", philo[i].number);
		
		philo[i].begin_of_starv = -1;
		do_timestamp("is eating", philo[i].number);
		usleep(philo[i].time_to_eat * 1000);
		
		pthread_mutex_unlock(&(g_forks[philo[i].second_fork]));
		pthread_mutex_unlock(&(g_forks[philo[i].first_fork]));
		philo[i].time_eat_for_die--;
		philo[i].begin_of_starv = get_current_time();
		do_timestamp("is sleeping", philo[i].number);
		usleep(philo[i].time_to_sleep * 1000);

		do_timestamp("is thinking", philo[i].number);
	}
}

void	run_life_of_philosophers(void)
{
	pthread_t	monitor;
	pthread_t	*threads;
	int	i;

	g_time_of_begin = get_current_time();
	i = -1;
	while (++i < g_number_of_philo)
	{
		if (i % 2 == 0)
			usleep(100000);
		pthread_create(&(philo[i].thread), NULL, begin_amazing_life, (void *)&(philo[i].number));
	}
	pthread_create(&(monitor), NULL, check_death, (void *)NULL);
	pthread_join(monitor, NULL);
}