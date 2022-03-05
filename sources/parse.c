/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:53:47 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/06 01:23:10 by minsunki         ###   ########seoul.kr  */
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

// static void	skip_sq(char **str)
// {
// 	*str = ft_strchr(*str + 1, '\'');
// 	if (!(*str))
// 		mexit_cm("TODO ERR MSG \' not closed", 255);
// 	(*str)++;
// }

static int	is_escape_c(char c)
{
	return (c == '\'' || c == '\\' || c == '\"' || c == '$');
}


static int	is_quote(char *str)
{
	return (*str != '\\' && (*(str + 1) == '\'' || *(str + 1) == '\"'));
}

static int	is_delim(char *str)
{
	if (*str == '\\')
		return (0);
	if ((*(str + 1) == '>' || *(str + 1) == '<' || *(str + 1) == '|'))
		return (1);
	if (ft_strncmp(str + 1, ">>", 2) == 0 ||
			ft_strncmp(str + 1, "<<", 2) == 0)
		return (1);
	return (0);
}

// static void	skip(char **str)
// {
// 	char	quote;

// 	quote = *(++str);
// 	(*str)++;
// 	while (*str)
// 	{
// 		if (is_quote(*str) && *str == quote)
// 			return ;
// 	}
// }

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
	//임시 코드
	t_token *ct = m->token_start;
	// printf("Tokens before expanding\n");
	// while (ct)
	// {
	// 	printf("#%s#id:%d\n",ct->str, ct->type);
	// 	ct = ct->next;
	// }
	expand(m);

	cleanup(m);	
	printf("\nFinal tokens\n");
	ct = m->token_start;
	while (ct)
	{
		printf("#%s#\n",ct->str);
		ct = ct->next;
	}
}

// void	parse(t_meta *m, char *line)
// {
// 	char	*cur;

// 	cur = skip_space(&line);
// 	while (*cur)
// 	{
// 		if (is_quote(cur))
// 			skip(&cur);
// 		else if (is_delim(cur))
// 		{

// 		}
// 		else if (ms_isspace(*cur))
// 		{
// 			add_token(m, line, cur);
// 			line = skip_space(&cur);
// 		}
// 	}
// }

// void	parse(t_meta *m, char *line)
// {
// 	char	*cur;

// 	skip_space(&line);
// 	cur = line;
// 	while (*cur)
// 	{
// 		if (*cur == '\'' || *cur == '\"')
// 			skip_quotes(&cur);
// 		else if (*cur == '<' || *cur == '>' || *cur == '|')
// 		{
// 			add_token(m, line, cur);
// 			line = cur++;
// 			if (*cur && *cur == '<' || *cur == '>')
// 				add_token(m, line, ++cur);
// 			else
// 				add_token(m, line, cur);
// 			line = cur;
// 		}
// 		else if (ms_isspace(*cur))
// 		{
// 			add_token(m, line, cur);
// 			skip_space(&cur);
// 			line = cur;
// 		}
// 		else
// 			cur++;
// 	}
// 	add_token(m, line, cur);
// 	token_ident_all(m);
// 	//임시 코드
// 	t_token *ct = m->token_start;
// 	printf("Tokens before expanding\n");
// 	while (ct)
// 	{
// 		printf("wat %s\n",ct->str);
// 		ct = ct->next;
// 	}
// 	// return ;
// 	// expand(m);

// 	// printf("\nTokens after expanding\n");
// 	// ct = m->token_start;
// 	// while (ct)
// 	// {
// 	// 	printf("%s\n",ct->str);
// 	// 	ct = ct->next;
// 	// }
	
// 	// unquote(m);
// 	cleanup(m);
// 	printf("\nTokens after un-quote\n");
// 	ct = m->token_start;
// 	while (ct)

// 	{
// 		printf("%s# ident: %u\n",ct->str, ct->type);
// 		ct = ct->next;
// 	}
// }
