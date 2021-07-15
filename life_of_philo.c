/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_of_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmisfit <nmisfit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 16:33:40 by nmisfit           #+#    #+#             */
/*   Updated: 2021/07/15 22:02:06 by nmisfit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

mls_t	get_current_time(void)
{
	struct timeval	current_time;
	mls_t	timestamp; //milliseconds

	gettimeofday(&current_time, NULL);
	
	// pthread_mutex_lock(&g_print);
	// printf("%ld\n", current_time.tv_sec);
	// pthread_mutex_unlock(&g_print);
	
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

void	*begin_amazing_life(void *ptr)
{
	t_philo *philo = (t_philo *)ptr;
	philo->time_of_starv = get_current_time();
	while (1)
	{
		pthread_mutex_lock(&(philo->first_fork));
		pthread_mutex_lock(&(philo->second_fork));
		philo->time_of_starv = 0;
		do_timestamp("is eating", philo->number);
		usleep(philo->time_to_eat);
		pthread_mutex_unlock(&(philo->second_fork));
		pthread_mutex_unlock(&(philo->first_fork));
		
		philo->time_of_starv = get_current_time();
		do_timestamp("is sleeping", philo->number);
		usleep(philo->time_to_sleep);

		do_timestamp("is thinking", philo->number);
	}
}

void	*check_death(void *ptr)
{
	int	i;
	int	death;
	mls_t	tmp;

	while (1)
	{
		i = -1;
		while (++i < g_number_of_philo)
		{
			tmp = get_current_time() - philo[i].time_of_starv;
			if (tmp >= philo[i].time_to_die)
			{
				mls_t	timestamp = get_current_time() - g_time_of_begin;;
				pthread_mutex_lock(&g_print);
				printf("%ld: number %d %s\n", timestamp, i + 1, "is die");
				exit(1);
			}
		}
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
		pthread_create(&(philo[i].thread), NULL, begin_amazing_life, (void *)&philo[i]);
	pthread_create(&(monitor), NULL, check_death, (void *)NULL);
	pthread_join(monitor, NULL);
}