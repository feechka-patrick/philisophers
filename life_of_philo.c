/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_of_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmisfit <nmisfit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 16:33:40 by nmisfit           #+#    #+#             */
/*   Updated: 2021/07/18 20:23:50 by nmisfit          ###   ########.fr       */
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
	mls_t	time_of_starv = 0;
	int	timer_eat = 0;

	while (1)
	{
		i = -1;
		if (g_philo[0].time_eat_for_die != -1)
			timer_eat = 1;
		while (++i < g_number_of_philo)
		{
			time_of_starv = get_current_time() - g_philo[i].begin_of_starv;
			if (g_philo[i].begin_of_starv != -1 && time_of_starv >= g_philo[i].time_to_die)
			{
				mls_t	timestamp = get_current_time() - g_time_of_begin;
				pthread_mutex_lock(&g_print);
				printf("%ld: number %d %s\n", timestamp, i + 1, "died");
				exit(1); //заменить
			}
			if (g_philo[i].time_eat_for_die != -1 && g_philo[i].time_eat_for_die != 0)
				timer_eat = 0;
		}
		if (timer_eat == 1)
		{
			pthread_mutex_lock(&g_print);
			break;
		}
	}
	return (NULL);
}

void	*begin_amazing_life(void *ptr)
{
	int i = *(int *)ptr - 1;
	g_philo[i].begin_of_starv = get_current_time();
	pthread_detach(g_philo[i].thread);
	while (1)
	{
		pthread_mutex_lock(&(g_forks[g_philo[i].first_fork]));
		do_timestamp("has taken a fork1", g_philo[i].number);
		pthread_mutex_lock(&(g_forks[g_philo[i].second_fork]));
		do_timestamp("has taken a fork2", g_philo[i].number);
		g_philo[i].begin_of_starv = get_current_time();
		
		do_timestamp("is eating", g_philo[i].number);
		myusleep(g_philo[i].time_to_eat * 1000);
		
		pthread_mutex_unlock(&(g_forks[g_philo[i].second_fork]));
		pthread_mutex_unlock(&(g_forks[g_philo[i].first_fork]));
		if (g_philo[i].time_eat_for_die != -1 && g_philo[i].time_eat_for_die != 0)
			g_philo[i].time_eat_for_die--;
		do_timestamp("is sleeping", g_philo[i].number);
		myusleep(g_philo[i].time_to_sleep * 1000);

		do_timestamp("is thinking", g_philo[i].number);
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
		if (i % 2 != 0)
			myusleep(100000);
		pthread_create(&(g_philo[i].thread), NULL, begin_amazing_life, (void *)&(g_philo[i].number));
		myusleep(100);
	}
	pthread_create(&(monitor), NULL, check_death, (void *)NULL);
	pthread_join(monitor, NULL);
}
