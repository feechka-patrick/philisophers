/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_function.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmisfit <nmisfit@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/15 15:22:06 by nmisfit           #+#    #+#             */
/*   Updated: 2021/07/15 17:21:33 by nmisfit          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	my_atoi(const char *nptr)
{
	int	sign;
	unsigned long	result;
	unsigned int	i;

	sign = 1;
	i = 0;
	if (nptr[i] == '-' || nptr[i] == '+')
		sign *= (nptr[i++] == '-') ? -1 : 1;
	result = 0;
	while (ft_isdigit(nptr[i]))
	{
		result = result * 10 + (nptr[i++] - '0');
		if (result > 2147483647 && sign == 1)
			return (-1);
		if (result > 2147483648 && sign == -1)
			return (0);
	}
	return ((int)(result * sign));
}

useconds_t	atoi_time(const char *nptr)
{
	unsigned int	result;
	unsigned int	i;

	i = 0;
	result = 0;
	while (ft_isdigit(nptr[i]))
		result = result * 10 + (nptr[i++] - '0');
	return ((useconds_t)(result * 1000));
}
