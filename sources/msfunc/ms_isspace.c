/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 02:52:06 by tjung             #+#    #+#             */
/*   Updated: 2022/03/03 00:16:37 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_isspace(char c)
{
	return ((9 <= c && c <= 13) || c == 32);
}

// null is not considered empty str.
int	ms_isemptystr(char *str)
{
	while (*str)
	{
		if (!ms_isspace(*str))
			return (0);
		str++;
	}
	return (1);
	// int	i;

	// i = -1;
	// while (str[++i])
	// {
	// 	if (str[i] < 9 || str[i] > 13)
	// 	{
	// 		if (str[i] == 32)
	// 			continue ;
	// 		return (0);
	// 	}
	// }
	// return (1);
}
