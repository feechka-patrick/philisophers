/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_of_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmisfit <nmisfit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 16:33:40 by nmisfit           #+#    #+#             */
/*   Updated: 2021/07/19 12:24:58 by nmisfit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_mls	get_current_time(void)
{
	struct timeval	current_time;
	t_mls			timestamp;

	gettimeofday(&current_time, NULL);
	timestamp = current_time.tv_sec * 1000 + current_time.tv_usec / 1000;
	return (timestamp);
}

void	do_timestamp(char *activity, int X)
{
	t_mls	timestamp;

	timestamp = get_current_time() - g_time_of_begin;
	pthread_mutex_lock(&g_print);
	printf("%ld: number %d %s\n", timestamp, X, activity);
	pthread_mutex_unlock(&g_print);
}

void	*check_death(void *ptr)
{
	int		i;
	t_mls	time_of_starv;
	int		timer_eat;

	//time_of_starv = *(int *)ptr;
	time_of_starv = 0;
	while (1)
	{
		i = -1;
		timer_eat = 1;
		while (++i < g_number_of_philo)
		{
			time_of_starv = get_current_time() - g_philo[i].begin_of_starv;
			if (g_philo[i].begin_of_starv != -1
				&& time_of_starv >= g_philo[i].time_to_die)
				return (exit_with_free(DEATH, i));
			if (g_philo[i].time_eat_for_die > 0)
				timer_eat = 0;
		}
		if (g_philo[0].time_eat_for_die != -1 && timer_eat == 1)
			return (exit_with_free(COUNT_OF_EAT, i));
		myusleep(100);
	}
}

void	*begin_amazing_life(void *ptr)
{
	int	i;

	i = *(int *)ptr - 1;
	pthread_detach(g_philo[i].thread);
	if (i % 2 != 0)
		myusleep(100);
	g_philo[i].begin_of_starv = get_current_time();
	while (1)
	{
		pthread_mutex_lock(&(g_forks[g_philo[i].first_fork]));
		do_timestamp("has taken a fork1", g_philo[i].number);
		pthread_mutex_lock(&(g_forks[g_philo[i].second_fork]));
		do_timestamp("has taken a fork2", g_philo[i].number);
		g_philo[i].begin_of_starv = get_current_time();
		do_timestamp("is eating", g_philo[i].number);
		myusleep(g_philo[i].time_to_eat);
		pthread_mutex_unlock(&(g_forks[g_philo[i].second_fork]));
		pthread_mutex_unlock(&(g_forks[g_philo[i].first_fork]));
		if (g_philo[i].time_eat_for_die > 0)
			g_philo[i].time_eat_for_die--;
		do_timestamp("is sleeping", g_philo[i].number);
		myusleep(g_philo[i].time_to_sleep);
		do_timestamp("is thinking", g_philo[i].number);
	}
}

void	run_life_of_philosophers(void)
{
	pthread_t	monitor;
	int			i;

	g_time_of_begin = get_current_time();
	i = -1;
	while (++i < g_number_of_philo)
	{
		pthread_create(&(g_philo[i].thread), NULL,
			begin_amazing_life, (void *)&(g_philo[i].number));
	}
	usleep(1000);
	pthread_create(&(monitor), NULL, check_death, NULL);
	pthread_join(monitor, NULL);
}
