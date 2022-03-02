/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:10:54 by minsunki          #+#    #+#             */
/*   Updated: 2021/08/03 15:23:34 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	checkset(char c, char const *set)
{
	while (*set)
		if (c == *set++)
			return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		s;
	int		e;
	char	*ret;

	if (!s1)
		return (0);
	if (!set)
		return (ft_strdup(s1));
	s = 0;
	e = ft_strlen(s1) - 1;
	while (checkset(s1[s], set))
		s++;
	if ((size_t)s == ft_strlen(s1))
		return (ft_strdup(""));
	while (checkset(s1[e], set))
		e--;
	ret = ft_substr(s1, s, e - s + 1);
	return (ret);
}
