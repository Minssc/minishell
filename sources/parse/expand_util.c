/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 01:08:24 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/07 01:08:41 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	while (*str)
	{
		if (*str == '\\')
			escape(&str);
		if (*str == '\'')
			skip_quotes(&str);
		else if (*str == '$' && *(str + 1) && !ms_isspace(*(str + 1))
					&& *(str + 1) != '\"')
			return (str);
		str++;
	}
	return (0);
}
