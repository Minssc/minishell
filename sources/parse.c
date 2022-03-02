/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:53:47 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/02 19:43:59 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
readline의 line 을 parse
| < << >> > 5개의 분리자를 기준으로 소분
예) a | b >> c
	a
	|
	b
	>>
	c
크기 5의 list 생성. 이때 앞뒤 공백 문자는 모두 삭제 (trim)

이후 subenv 함수에서 리스트 순회 하며 environment variable을 삽입. 
*/


static void	add_arg(t_meta *m, char *from, char *to)
{
	char	*cont;
	char	*tmp;
	t_list	*nl;
	
	cont = ft_substr(from, 0, to - from);
	tmp = cont;
	cont = ft_strtrim(cont, " \n\r\t"); // TODO "공백 문자 더 있나?"
	if (!cont)
		perror_exit("ft_substr failed @add_arg");
	nl = ft_lstnew(cont);
	if (!nl)
		perror_exit("ft_lstnew failed @add_arg");
	ft_lstadd_back(&m->list_args, nl);
}

static void	find_and_sub(t_list *li)
{
	char	*cur;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	int		i;

	cur = (char *)li->content;
	while (*cur)
	{
		i = 0;
		if (*cur == '\'')
		{
			cur++;
			while (*cur && *cur != '\'')
				cur++;
			if (!*cur)
				break ;
		}
		if (*cur == '$') // TODO $? $$ $< 등등?
		{
			tmp = li->content;
			li->content = ft_substr(li->content, 0,
				cur - (char *)li->content);
			while (cur[i] && cur[i] != ' ' && cur[i] != '\"') // TODO make a func for "empty" space
				i++;
			tmp3 = ft_substr(cur, 1, i - 1);
			tmp2 = li->content;
			li->content = ft_strjoin(li->content, getenv(tmp3));
			free(tmp3);
			free(tmp2);
			tmp2 = li->content;
			li->content = ft_strjoin(li->content, cur + i);
			free(tmp2);
			free(tmp);
			cur = (char *)li->content;
			printf("%s\n",(char *)cur);
		}
		cur++;
	}
}

static void	sub_env(t_meta *m)
{
	t_list	*cl;

	cl = m->list_args;
	while (cl)
	{
		find_and_sub(cl);
		cl = cl->next;
	}
}

void	parse(t_meta *m, char *line)
{
	t_list	*nl;
	char	*args;
	char	*cur;
	char	*tmp;

	args = 0;
	cur = line;
	while (*line && *cur)
	{
		if (*cur == '|' || *cur == '<' || *cur == '>') // TODO ||의 경우는 지금 처리? 후 처리?
		{
			add_arg(m, line, cur);
			line = cur++;
			if (*cur && (*cur == '<' || *cur == '>'))
				cur++;
			add_arg(m, line, cur);
			line = cur;
		}
		cur++;
	}
	if (*line)
		add_arg(m, line, cur);
	
	t_list *cl;
	
	cl = m->list_args;
	while (cl)
	{
		printf("cont orig: #%s#\n", (char *)cl->content);
		cl = cl->next;
	}
	sub_env(m);	
	cl = m->list_args;
	while (cl)
	{
		printf("cont after sub: #%s#\n", (char *)cl->content);
		cl = cl->next;
	}
	ft_lstclear(&m->list_args, free);

}