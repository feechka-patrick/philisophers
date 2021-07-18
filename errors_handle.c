/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmisfit <nmisfit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 15:04:25 by nmisfit           #+#    #+#             */
/*   Updated: 2021/07/18 19:26:02 by nmisfit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	my_strerror(char *message)
{
	printf("%s\n", message);
	exit(1);
}

void	exit_with_free()
{
	free(g_forks);
	free(g_philo);
	exit(1);
}