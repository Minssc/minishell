/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 13:05:11 by minsunki          #+#    #+#             */
/*   Updated: 2021/08/03 15:22:38 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	unsigned long long	result;
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
	if (result > 2147483647 && !is_neg)
		return (-1);
	if (result > 2147483648 && is_neg)
		return (0);
	if (is_neg)
		return (-result);
	return (result);
}
