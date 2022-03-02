/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_trim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:56:38 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/02 16:16:59 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*ms_trim(char *str)
// str 문자열의 앞뒤 공백을 제거함. ' ', '\t'
// 전달받은 str 포인터는 free하지 않으니 주의!

char	*ms_trim(char *str)
{
	int		i;
	char	*ret;
	char	*tmp;
	size_t	slen;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	ret = ft_strdup(str + i);
	slen = ft_strlen(ret);
	i = slen - 1;
	while (ret[i] == ' ' || ret[i] == '\t')
		i--;
	if (i != slen - 1)
	{
		ret[i + 1] = '\0';
		tmp = ret;
		ret = ft_strdup(ret);
		free(tmp);
	}
	return (ret);
}
