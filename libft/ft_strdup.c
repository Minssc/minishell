/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 13:10:54 by minsunki          #+#    #+#             */
/*   Updated: 2021/08/03 15:23:28 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	size_t	slen;
	char	*nstr;

	slen = ft_strlen(str);
	nstr = (char *)malloc(sizeof(char) * (slen + 1));
	if (!nstr)
		return (0);
	ft_strlcpy(nstr, str, slen + 1);
	return (nstr);
}
