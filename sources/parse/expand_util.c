/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 01:08:24 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/10 22:59:04 by tjung            ###   ########.fr       */
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
