/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmisfit <nmisfit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 15:22:06 by nmisfit           #+#    #+#             */
/*   Updated: 2021/07/19 12:29:27 by nmisfit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_isdigit(char c)
{
	if (c <= '9' && c >= '0')
		return (1);
	return (0);
}

int	my_atoi(const char *nptr)
{
	unsigned long	result;
	unsigned int	i;

	i = 0;
	result = 0;
	while (ft_isdigit(nptr[i]))
	{
		result = result * 10 + (nptr[i++] - '0');
		if (result > 2147483647)
			return (-1);
	}
	return ((int)(result));
}

t_mls	atoi_time(const char *nptr)
{
	unsigned int	result;
	unsigned int	i;

	i = 0;
	result = 0;
	while (ft_isdigit(nptr[i]))
		result = result * 10 + (nptr[i++] - '0');
	return ((t_mls)(result));
}

void	myusleep(t_mls time)
{
	t_mls	begin;

	begin = get_current_time();
	while (get_current_time() - begin < time)
		usleep(1000);
}
