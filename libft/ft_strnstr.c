/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 13:12:55 by minsunki          #+#    #+#             */
/*   Updated: 2021/08/03 15:23:33 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	nlen;

	nlen = ft_strlen(needle);
	if (!needle[0])
		return ((char *)haystack);
	if (!len)
		return (0);
	while (len-- && ft_strncmp(haystack, needle, nlen) != 0)
	{
		if (len < nlen || !(*haystack))
			return (0);
		haystack++;
	}
	return ((char *)haystack);
}
