/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 18:49:23 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/10 15:47:53 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 기본적으로 ft_substr와 같이 동작하지만 len이 절대적으로 고정.
// 기존 unsigned 변수 size_t에서 signed int로 len type 변경. 음수일 시 len=0취급.
// 만약 len == 0이라면 ft_strdup("") 반환

char	*ms_substr(char const *s, unsigned int start, int len)
{
	char	*dmem;

	if (!s)
		return (0);
	if ((unsigned int)ft_strlen(s) < start || len <= 0)
		return (ft_strdup(""));
	if ((int)ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	dmem = (char *)malloc(sizeof(char) * (len + 1));
	if (!dmem)
		return (0);
	ft_strlcpy(dmem, s + start, len + 1);
	return (dmem);
}
