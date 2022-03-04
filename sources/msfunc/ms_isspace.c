/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 02:52:06 by tjung             #+#    #+#             */
/*   Updated: 2022/03/03 12:28:43 by tjung            ###   ########.fr       */
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
}
