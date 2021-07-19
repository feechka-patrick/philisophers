/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmisfit <nmisfit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 15:04:25 by nmisfit           #+#    #+#             */
/*   Updated: 2021/07/19 12:15:32 by nmisfit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	my_strerror(char *message)
{
	printf("%s\n", message);
	if (g_forks)
		free(g_forks);
	if (g_philo)
		free(g_philo);
	return (0);
}

void	*exit_with_free(int flag, int X)
{
	t_mls	timestamp;

	timestamp = get_current_time() - g_time_of_begin;
	pthread_mutex_lock(&g_print);
	if (flag == DEATH)
		printf("%ld: number %d %s\n", timestamp, X + 1, "died");
	if (g_forks)
		free(g_forks);
	if (g_philo)
		free(g_philo);
	return (NULL);
}
