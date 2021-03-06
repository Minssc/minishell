/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_util_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 01:08:24 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/12 12:03:05 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	escape(char **str)
{
	char	nc;

	nc = *(*str + 1);
	(*str)++;
	if (nc == '\"' || nc == '$')
		(*str)++;
}

static void	skip_quotes(char **str)
{
	char	quote;

	quote = **str;
	(*str)++;
	while (**str)
	{
		if (**str == '\\')
			escape(str);
		if (**str == quote)
			break ;
		else
			(*str)++;
	}
}

char	*find_e(char *str)
{
	int	dq;

	dq = 0;
	while (*str)
	{
		if (*str == '\\')
			escape(&str);
		if (!dq && *str == '\'')
			skip_quotes(&str);
		else if (*str == '$' && *(str + 1) && !ms_isspace(*(str + 1))
			&& *(str + 1) != '\"')
			return (str);
		else if (*str == '\"')
			dq ^= Q_DQ;
		str++;
	}
	return (0);
}
