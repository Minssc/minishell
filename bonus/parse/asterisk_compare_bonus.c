/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk_compare_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 00:11:46 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/12 12:03:05 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	compare(char **hay, char **str)
{
	int	ast;

	ast = 0;
	while ((**str) && (**str) != '/')
	{
		if (!(**hay))
			return ;
		if ((**str) == '\\' && *(++(*str)) == '*')
		{
			(*str)++;
			continue ;
		}
		if ((**str) == '*')
		{
			while ((**str) == '*')
				(*str)++;
			*hay = ft_strchr(*hay, **str);
			if (!(*hay))
				return ;
		}
		if ((**str) != (**hay))
			return ;
	}
}

int	asterisk_compare(char *dir, char *hay, char *str)
{
	// compare(&hay, &str);
	printf("%s, %s\n",hay,str);
	if (*hay || (*str && *hay && *hay != *str))
		return (0);
	while (*str && *str != '/')
	{
		if (*str != '*')
			return (0);
		str++;
	}
	return (1);
}