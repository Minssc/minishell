/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/06 20:12:37 by minsunki          #+#    #+#             */
/*   Updated: 2021/08/03 15:23:10 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_mini(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

size_t	ft_mins(size_t a, size_t b)
{
	if (a < b)
		return (a);
	return (b);
}

long long	ft_minll(long long a, long long b)
{
	if (a < b)
		return (a);
	return (b);
}

float	ft_minf(float a, float b)
{
	if (a < b)
		return (a);
	return (b);
}

double	ft_mind(double a, double b)
{
	if (a < b)
		return (a);
	return (b);
}
