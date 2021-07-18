/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmisfit <nmisfit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 16:36:27 by nmisfit           #+#    #+#             */
/*   Updated: 2021/07/18 20:33:37 by nmisfit          ###   ########.fr       */
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
typedef unsigned int	mks_t;
typedef long	mls_t;

typedef struct s_all
{
	int	number_of_philo;
	mls_t	time_to_die;
	mls_t	time_to_eat;
	mls_t	time_to_sleep;
	int	time_eat_for_die;
}	t_all;

typedef struct s_philo
{
	int	number;
	pthread_t	thread;
	int	first_fork;
	int	second_fork;
	mls_t	time_to_die;
	mls_t	time_to_eat;
	mls_t	time_to_sleep;
	mls_t	begin_of_starv;
	int	time_eat_for_die;
}	t_philo;

mls_t	g_time_of_begin;
mutex_t	*g_forks;
mutex_t	g_print;
t_philo *g_philo;
int	g_number_of_philo;

int	my_atoi(const char *nptr);
mls_t	atoi_time(const char *nptr);
void	my_strerror(char *message);
mls_t	get_current_time(void);
void	myusleep(mls_t time);
void	run_life_of_philosophers(void);

#endif