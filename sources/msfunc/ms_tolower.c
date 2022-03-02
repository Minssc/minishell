/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:20:48 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/02 16:22:41 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*ms_tolower(char *str)
// 전달받은 str을 모두 소문자로 변경

char	*ms_tolower(char *str)
{
	while (*str)
		*str = ft_tolower(*str);
}