/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmisfit <nmisfit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 15:04:25 by nmisfit           #+#    #+#             */
/*   Updated: 2021/08/03 11:36:53 by nmisfit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	my_strerror(char *message, t_global *info)
{
	printf("%s\n", message);
	if (info && info->forks)
		free(info->forks);
	if (info && info->philo)
		free(info->philo);
	if (info && info->print)
		free(info->print);
	return (0);
}

void	*exit_with_free(int flag, int X, t_global *info)
{
	t_mls	timestamp;

	timestamp = get_current_time() - info->time_of_begin;
	pthread_mutex_lock(info->print);
	if (flag == DEATH)
		printf("%ld: number %d %s\n", timestamp, X + 1, "died");
	if (info->forks)
		free(info->forks);
	if (info->philo)
		free(info->philo);
	if (info->print)
		free(info->print);
	return (NULL);
}
