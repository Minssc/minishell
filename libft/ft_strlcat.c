/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 13:17:30 by minsunki          #+#    #+#             */
/*   Updated: 2021/08/03 15:23:30 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	dlen;
	size_t	slen;

	dlen = ft_strlen(dest);
	slen = ft_strlen(src);
	i = 0;
	if (size < dlen + 1)
		return (size + slen);
	if (size > dlen + 1)
	{
		while (src[i] != '\0' && dlen + 1 + i < size)
		{
			dest[dlen + i] = src[i];
			i++;
		}
	}
	dest[dlen + i] = '\0';
	return (dlen + slen);
}
