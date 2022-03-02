/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 13:03:11 by minsunki          #+#    #+#             */
/*   Updated: 2021/08/03 15:22:55 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_digs(int n)
{
	int		ret;

	ret = (n <= 0);
	while (n)
	{
		n /= 10;
		ret++;
	}
	return (ret);
}

char	*ft_itoa(int n)
{
	int		dig;
	int		neg;
	char	*ret;

	neg = (n < 0);
	dig = ft_digs(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	ret = (char *)malloc(sizeof(char) * (dig + 1));
	if (!ret)
		return (0);
	ret[dig] = 0;
	if (n < 0)
		n = -n;
	while (dig--)
	{
		ret[dig] = '0' + (n % 10);
		n /= 10;
	}
	if (neg)
		ret[0] = '-';
	return (ret);
}
