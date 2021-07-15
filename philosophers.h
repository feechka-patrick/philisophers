/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmisfit <nmisfit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 16:36:27 by nmisfit           #+#    #+#             */
/*   Updated: 2021/07/15 21:48:04 by nmisfit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef pthread_mutex_t	mutex_t;
typedef useconds_t	mks_t;
typedef long	mls_t;

typedef struct s_all
{
	int	number_of_philo;
	mks_t	time_to_die;
	mks_t	time_to_eat;
	mks_t	time_to_sleep;
	int	*n_eat;
}	t_all;

typedef struct s_philo
{
	int	number;
	pthread_t	thread;
	pthread_mutex_t	first_fork;
	pthread_mutex_t	second_fork;
	mks_t	time_to_die;
	mks_t	time_to_eat;
	mks_t	time_to_sleep;
	mls_t	time_of_starv;
}	t_philo;

mls_t	g_time_of_begin;
mutex_t	*g_forks;
mutex_t	g_print;
t_philo *philo;
int	g_number_of_philo;

int	my_atoi(const char *nptr);
useconds_t	atoi_time(const char *nptr);
void	my_strerror(char *message);
void	run_life_of_philosophers(void);

#endif