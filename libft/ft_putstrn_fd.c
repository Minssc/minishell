/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstrn_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 14:25:59 by minsunki          #+#    #+#             */
/*   Updated: 2021/08/03 15:23:15 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstrn_fd(char *s, int fd, size_t len)
{
	if (!s || fd < 0)
		return ;
	len = ft_mins(ft_strlen(s), len);
	write(fd, s, len);
}
