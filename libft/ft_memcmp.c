/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 13:04:06 by minsunki          #+#    #+#             */
/*   Updated: 2021/08/03 15:23:06 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*sp1;
	unsigned char	*sp2;
	int				ret;

	sp1 = (unsigned char *)s1;
	sp2 = (unsigned char *)s2;
	while (n--)
	{
		ret = (*sp1++ - *sp2++);
		if (ret)
			return (ret);
	}
	return (0);
}
