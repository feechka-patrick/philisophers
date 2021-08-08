/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_of_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmisfit <nmisfit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 16:33:40 by nmisfit           #+#    #+#             */
/*   Updated: 2021/08/03 11:35:42 by nmisfit          ###   ########.fr       */
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

void	do_timestamp(char *activity, t_philo philo)
{
	t_mls	timestamp;

	timestamp = get_current_time() - philo.time_of_begin;
	pthread_mutex_lock(philo.print);
	printf("%ld: number %d %s\n", timestamp, philo.number, activity);
	pthread_mutex_unlock(philo.print);
}

void	*check_death(void *ptr)
{
	int			i;
	t_mls		time_of_starv;
	int			timer_eat;
	t_global	*info;

	info = (t_global *)ptr;
	time_of_starv = 0;
	while (1)
	{
		i = -1;
		timer_eat = 1;
		while (++i < info->number_of_philo)
		{
			time_of_starv = get_current_time() - info->philo[i].begin_of_starv;
			if (info->philo[i].begin_of_starv != -1
				&& time_of_starv >= info->philo[i].time_to_die)
				return (exit_with_free(DEATH, i, info));
			if (info->philo[i].time_eat_for_die > 0)
				timer_eat = 0;
		}
		if (info->philo[0].time_eat_for_die != -1 && timer_eat == 1)
			return (exit_with_free(COUNT_OF_EAT, i, info));
		myusleep(5);
	}
}

void	*begin_amazing_life(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	pthread_detach(philo->thread);
	if (philo->number % 2 == 0)
		myusleep(100);
	philo->begin_of_starv = get_current_time();
	while (1)
	{
		pthread_mutex_lock(philo->first_fork);
		do_timestamp("has taken a fork1", *philo);
		pthread_mutex_lock(philo->second_fork);
		do_timestamp("has taken a fork2", *philo);
		philo->begin_of_starv = get_current_time();
		do_timestamp("is eating", *philo);
		myusleep(philo->time_to_eat);
		pthread_mutex_unlock(philo->second_fork);
		pthread_mutex_unlock(philo->first_fork);
		if (philo->time_eat_for_die > 0)
			philo->time_eat_for_die--;
		do_timestamp("is sleeping", *philo);
		myusleep(philo->time_to_sleep);
		do_timestamp("is thinking", *philo);
	}
}

void	run_life_of_philosophers(t_global *info)
{
	pthread_t	monitor;
	int			i;

	info->time_of_begin = get_current_time();
	i = -1;
	while (++i < info->number_of_philo)
	{
		info->philo[i].time_of_begin = info->time_of_begin;
		pthread_create(&(info->philo[i].thread), NULL,
			begin_amazing_life, (void *)&(info->philo[i]));
		usleep(100);
	}
	usleep(100);
	pthread_create(&(monitor), NULL, check_death, (void *)info);
	pthread_join(monitor, NULL);
}
