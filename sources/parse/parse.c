/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:53:47 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/09 22:41:31 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*skip_space(char **str)
{
	while (ms_isspace(**str))
		(*str)++;
	return (*str);
}

static void	escape(char **str)
{
	char	nc;

	nc = *(*str + 1);
	(*str)++;
	if (nc == '\'' || nc == '\"' || nc == '|')
		(*str)++;
	if (nc == '<' || nc == '>')
		(*str)++;
}

static void	skip_quotes(char **str)
{
	char	quote;

	quote = **str;
	(*str)++;
	while (**str)
	{
		if (quote == '\"' && (**str) == '\\' && *(*str + 1) == '\"')
			escape(str);
		if (quote == **str)
		{
			(*str)++;
			break ;
		}
		else
			(*str)++;
	}
}

static void	delim(t_meta *m, char **line, char **cur)
{
	token_parse(m, *line, *cur);
	*line = (*cur)++;
	if (**cur && **cur == '<' || **cur == '>')
		token_parse(m, *line, ++(*cur));
	else
		token_parse(m, *line, *cur);
	*line = *cur;			
}

void	parse(t_meta *m, char *line)
{
	char	*cur;

	cur = skip_space(&line);
	while (*cur)
	{
		if (*cur == '\\')
			escape(&cur);
		if (*cur == '\'' || *cur == '\"')
			skip_quotes(&cur);
		else if (*cur == '>' || *cur == '<' || *cur == '|')
			delim(m, &line, &cur);
		else if (ms_isspace(*cur))
		{
			token_parse(m, line, cur);
			line = skip_space(&cur);
		}
		else
			cur++;
	}
	token_parse(m, line, cur);
	sort_tokens(m);
	heredoc_init(m);
	expand(m);
	cleanup(m);	
}
