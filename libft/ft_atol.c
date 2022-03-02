/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 13:05:11 by minsunki          #+#    #+#             */
/*   Updated: 2021/08/03 15:22:39 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atol(const char *str)
{
	long long			result;
	int					is_neg;

	while (ft_strchr(" \v\t\r\n\f", *str))
		str++;
	is_neg = (*str == '-');
	if (*str == '+' || *str == '-')
		str++;
	result = 0;
	while ('0' <= *str && *str <= '9')
	{
		result *= 10;
		result += *str - '0';
		str++;
	}
	if (is_neg)
		return (-result);
	return (result);
}
