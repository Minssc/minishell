/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 13:20:05 by minsunki          #+#    #+#             */
/*   Updated: 2021/08/03 15:23:05 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*dp;
	unsigned char	*sp;
	size_t			i;

	dp = (unsigned char *)dest;
	sp = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		dp[i] = sp[i];
		if (sp[i] == (unsigned char)c)
			return (dp + i + 1);
		i++;
	}
	return (0);
}
