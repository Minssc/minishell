/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tolower_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:20:48 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/12 13:37:43 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

// char	*ms_tolower(char *str)
// 전달받은 str을 모두 소문자로 변경

char	*ms_tolower(char *str)
{
	char	*ret;

	ret = str;
	while (*str)
	{
		*str = ft_tolower(*str);
		str++;
	}
	return (ret);
}
