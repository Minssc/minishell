/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 20:11:19 by minsunki          #+#    #+#             */
/*   Updated: 2021/08/03 15:23:04 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_maxi(int a, int b)
{
	if (a < b)
		return (b);
	return (a);
}

size_t	ft_maxs(size_t a, size_t b)
{
	if (a < b)
		return (b);
	return (a);
}

long long	ft_maxll(long long a, long long b)
{
	if (a < b)
		return (b);
	return (a);
}

float	ft_maxf(float a, float b)
{
	if (a < b)
		return (b);
	return (a);
}

double	ft_maxd(double a, double b)
{
	if (a < b)
		return (b);
	return (a);
}
