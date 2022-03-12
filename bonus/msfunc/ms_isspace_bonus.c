/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_isspace_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 02:52:06 by tjung             #+#    #+#             */
/*   Updated: 2022/03/12 12:03:05 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

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
}
