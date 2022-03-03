/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:53:47 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/03 18:15:26 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// token 기준 parsing 
// parsing 후 환경변수 삽입 
// 환경변수 삽입 후 따옴표 제거 


// static void	add_arg(t_meta *m, char *from, char *to)
// {
// 	char	*cont;
// 	char	*tmp;
// 	t_list	*nl;
	
// 	cont = ft_substr(from, 0, to - from);
// 	tmp = cont;
// 	cont = ft_strtrim(cont, " \n\r\t"); // TODO "공백 문자 더 있나?"
// 	if (!cont)
// 		perror_exit("ft_substr failed @add_arg");
// 	nl = ft_lstnew(cont);
// 	if (!nl)
// 		perror_exit("ft_lstnew failed @add_arg");
// 	ft_lstadd_back(&m->list_args, nl);
// }


static void	skip_space(char **str)
{
	while (ms_isspace(**str))
		(*str)++;
}

void		ms_skip_quotes(char **str, char quote)
{
	*str = ft_strchr(*str + 1, quote);
	if (!(*str))
		mexit_cm("syntax err \' or \"", 255);
	(*str)++;
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
	if (!m->token_start)
		m->token_start = nt;
	else
	{
		lt = m->token_start;
		while (lt && lt->next)
			lt = lt->next;
		lt->next = nt;
		nt->prev = lt;
	}
	printf("CT S:%s\n",nt->str);
}

void	parse(t_meta *m, char *line)
{
	char	*cur;

	skip_space(&line);
	cur = line;
	while (*cur)
	{
		if (*cur == '\"' || *cur == '\'')
			ms_skip_quotes(&cur, *cur);
		else if (*cur == '<' || *cur == '>' || *cur == '|')
		{
			add_token(m, line, cur);
			line = cur++;
			if (*cur && *cur == '<' || *cur == '>')
				add_token(m, line, ++cur);
			else
				add_token(m, line, cur);
			line = cur;
		}
		else if (ms_isspace(*cur))
		{
			add_token(m, line, cur);
			skip_space(&cur);
			line = cur;
		}
		else
			cur++;
	}
	add_token(m, line, cur);
	expand(m);
	
	m->token_start = 0;
	// printf("leftover: #%s#\n",line);
	// t_list	*nl;
	// char	*args;
	// char	*cur;
	// char	*tmp;

	// args = 0;
	// cur = line;
	// while (*line && *cur)
	// {
	// 	if (*cur == '\"')
	// 	{
	// 		cur++;
	// 		while (*cur && *cur != '\"')
	// 			cur++;
	// 		if (!*cur){
	// 			printf("minishell: syntax error: unexpected EOF while looking for matching \'\"\'\n");
	// 			break ;
	// 		}	
	// 	}
	// 	if (*cur == '|' || *cur == '<' || *cur == '>') // TODO ||의 경우는 지금 처리? 후 처리?
	// 	{
	// 		add_arg(m, line, cur);
	// 		line = cur++;
	// 		if (*cur && (*cur == '<' || *cur == '>'))
	// 			cur++;
	// 		add_arg(m, line, cur);
	// 		line = cur;
	// 	}
	// 	cur++;
	// }
	// if (*line)
	// 	add_arg(m, line, cur);
	
	// t_list *cl;
	
	// cl = m->list_args;
	// while (cl)
	// {
	// 	printf("cont orig: #%s#\n", (char *)cl->content);
	// 	cl = cl->next;
	// }
	// sub_env(m);	
	// cl = m->list_args;
	// while (cl)
	// {
	// 	printf("cont after sub: #%s#\n", (char *)cl->content);
	// 	cl = cl->next;
	// }
	// ft_lstclear(&m->list_args, free);

}