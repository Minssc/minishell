/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 13:20:59 by minsunki          #+#    #+#             */
/*   Updated: 2021/08/03 15:23:08 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*pd;
	unsigned char	*ps;

	pd = (unsigned char *)dest;
	ps = (unsigned char *)src;
	if (dest == src || n == 0)
		return (dest);
	if (pd < ps)
	{
		while (n--)
			*pd++ = *ps++;
	}
	else
	{
		while (n--)
			pd[n] = ps[n];
	}
	return (dest);
}
