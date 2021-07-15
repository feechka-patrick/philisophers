/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life_of_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmisfit <nmisfit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 16:33:40 by nmisfit           #+#    #+#             */
/*   Updated: 2021/07/15 17:27:03 by nmisfit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	get_timestamp(char *activity, int X)
{
	struct timeval	current_time;
	long	timestamp; //microseconds

	gettimeofday(&current_time, NULL);
	timestamp = current_time.tv_sec * 1000 - g_time_of_begin;
	printf("%ld: number %d %s\n", timestamp, X, activity);
}

void	*begin_amazing_life(void *ptr)
{
	t_philo *philo = (t_philo *)ptr;
	
	pthread_mutex_lock(&(philo->first_fork));
	pthread_mutex_lock(&(philo->second_fork));
	
	get_timestamp("is eating", philo->number);
	usleep(philo->time_to_eat);
	
	pthread_mutex_unlock(&(philo->second_fork));
	pthread_mutex_unlock(&(philo->first_fork));
	
	get_timestamp("is sleeping", philo->number);
	usleep(philo->time_to_sleep);
	
	get_timestamp("is die", philo->number);
}
