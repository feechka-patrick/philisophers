/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmisfit <nmisfit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 16:36:27 by nmisfit           #+#    #+#             */
/*   Updated: 2021/07/19 12:31:21 by nmisfit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

# define DEATH 1
# define COUNT_OF_EAT 0

typedef pthread_mutex_t	t_mutex;
typedef unsigned int	t_mks;
typedef long			t_mls;

typedef struct s_all
{
	int		number_of_philo;
	t_mls	time_to_die;
	t_mls	time_to_eat;
	t_mls	time_to_sleep;
	int		time_eat_for_die;
}	t_all;

typedef struct s_philo
{
	int			number;
	pthread_t	thread;
	int			first_fork;
	int			second_fork;
	t_mls		time_to_die;
	t_mls		time_to_eat;
	t_mls		time_to_sleep;
	t_mls		begin_of_starv;
	int			time_eat_for_die;
}	t_philo;

t_mls					g_time_of_begin;
t_mutex					*g_forks;
t_mutex					g_print;
t_philo					*g_philo;
int						g_number_of_philo;

int			my_atoi(const char *nptr);
t_mls		atoi_time(const char *nptr);
int			my_strerror(char *message);
t_mls		get_current_time(void);
void		myusleep(t_mls time);
void		*exit_with_free(int flag, int X);
void		run_life_of_philosophers(void);

#endif