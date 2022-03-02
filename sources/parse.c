/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:53:47 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/02 18:35:33 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		printf("cont: %s$\n", (char *)cl->content);
		cl = cl->next;
	}
	ft_lstclear(&m->list_args, free);
}