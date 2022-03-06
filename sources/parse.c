/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:53:47 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/07 00:27:30 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// token 기준 parsing 
// parsing 후 환경변수 삽입 
// 환경변수 삽입 후 따옴표 제거 

static char	*skip_space(char **str)
{
	while (ms_isspace(**str))
		(*str)++;
	return (*str);
}

static void	add_token(t_meta *m, char *from, char *to)
{
	t_token *lt;
	t_token	*nt;

	if (from >= to)
		return ;
	nt = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (!nt)
		perror_exit("ft_calloc failed @add_token");
	nt->str = ft_substr(from, 0, to - from);
	if (!nt->str)
		perror_exit("ft_substr failed @add_token");
	token_ident(nt);
	token_add_back(&m->token_start, nt);
}

static void	escape(char **str)
{
	char	nc;
	char	nnc;

	nc = *(*str + 1);
	nnc = 0;
	if (nc)
		nnc = *(*str + 2);
	(*str)++;
	if (nc == '\'' || nc == '\"' || nc == '|')
		(*str)++;
	if (nc == '<' || nc == '>')
		(*str)++;
	// if (nc == nnc)
	// 	(*str)++;
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
	add_token(m, *line, *cur);
	*line = (*cur)++;
	if (**cur && **cur == '<' || **cur == '>')
		add_token(m, *line, ++(*cur));
	else
		add_token(m, *line, *cur);
	*line = *cur;			
}

static int	stop_moving(t_token *tok)
{
	t_token	*prev;

	if (!tok || (tok->type & (T_CMD | T_ARG)))
	{
		prev = token_prev_delim(tok);
		if (!prev || (prev->type & T_PIP))
			return (1);
	}
	return (0);
}

static void	insert_token(t_meta *m, t_token *tok, t_token *bef)
{
	tok->prev->next = tok->next;
	if (tok->next)
		tok->next->prev = tok->prev;
	if (!bef)
	{
		m->token_start->prev = tok;
		tok->next = m->token_start;
		m->token_start = tok;
		tok->prev = 0;
	}
	else
	{
		tok->prev = bef;
		tok->next = bef->next;
		if (bef->next)
			bef->next->prev = tok;
		bef->next = tok;
	}
}

static void	sort_args(t_meta *m)
{
	t_token	*cur;
	t_token	*prev;

	cur = m->token_start;
	while (cur)
	{
		prev = token_prev_delim(cur);
		if (cur->type == T_ARG && prev && (prev->type & REDIR))
		{
			while (!stop_moving(prev))
				prev = prev->prev;
			insert_token(m, cur, prev);
		}
		cur = cur->next;
	}
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
			add_token(m, line, cur);
			line = skip_space(&cur);
		}
		else
			cur++;
	}
	add_token(m, line, cur);
	token_ident_all(m);
	sort_args(m);
	//임시 코드
	t_token *ct = m->token_start;
	expand(m);
	cleanup(m);	
	// printf("\nFinal tokens\n");
	// ct = m->token_start;
	// while (ct)
	// {
	// 	printf("#%s#id:%d\n",ct->str,ct->type);
	// 	ct = ct->next;
	// }
}
