/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_argjoin_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 16:32:36 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/12 12:03:05 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

// char	*ms_argjoin(char *s1, char *s2)
// ft_strjoin과 같으나 중간에 공백 삽입
char	*ms_argjoin(char const *s1, char const *s2)
{
	char	*ret;
	int		s1_len;
	int		s2_len;

	if (!s1 && !s2)
		return (0);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ret = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1 + 1));
	if (!ret)
		return (0);
	ft_strlcpy(ret, s1, s1_len + 1);
	ret[s1_len] = ' ';
	ft_strlcat(ret + s1_len + 1, s2, s2_len + 1);
	return (ret);
}
