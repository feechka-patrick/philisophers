/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmisfit <nmisfit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 16:36:27 by nmisfit           #+#    #+#             */
/*   Updated: 2021/07/15 17:29:32 by nmisfit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

long	g_time_of_begin;
mutex_t	*g_forks;

typedef pthread_mutex_t mutex_t;

typedef struct s_all
{
	int	number_of_philo;
	useconds_t	time_to_die;
	useconds_t	time_to_eat;
	useconds_t	time_to_sleep;
	int	*n_eat;
}	t_all;

typedef struct s_philo
{
	int	number;
	pthread_t	thread;
	pthread_mutex_t	first_fork;
	pthread_mutex_t	second_fork;
	useconds_t	time_to_die;
	useconds_t	time_to_eat;
	useconds_t	time_to_sleep;
}	t_philo;


#endif