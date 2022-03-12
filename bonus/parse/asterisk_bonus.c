/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 18:44:00 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/12 12:03:05 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static char	*reverse_find_dir(char *begin, char *cur)
{
	while (--cur >= begin)
		if (*cur == '/')
			return (cur);
	return (0);
}

static void	asterisk_proc_list(t_list *list)
{
	char	*cur_as;
	char	*last_dir;
	char	*str;

	str = (char *)list->content;
	cur_as = find_ast(str);
	if (!cur_as)
		return ;
	last_dir = reverse_find_dir(str, cur_as);
	if (last_dir)
	{
		last_dir = ft_substr(str, 0, (int)(last_dir - str) + 1);
		asterisk_read_dir(list, last_dir, reverse_find_dir(str, cur_as) + 1);
		free(last_dir);
	}
	else
		asterisk_read_dir(list, 0, str);
	free(list->content);
	list->content = 0;
}

static int	add_tokens(t_token *tok, t_list *list)
{
	int		ret;
	t_token	*nt;

	ret = 0;
	while (list)
	{
		if (list->content)
		{
			nt = (t_token *)ft_calloc(sizeof(t_token), 1);
			nt->str = ft_strdup((char *)list->content);
			nt->prev = tok;
			nt->next = tok->next;
			if (tok->next)
				tok->next->prev = nt;
			tok->next = nt;
			ret++;
		}
		list = list->next;
	}
	return (ret);
}

static void	asterisk_process(t_meta *m, t_token *tok)
{
	t_list	*list_names;
	t_list	*list;

	list = ft_lstnew(ft_strdup(tok->str));
	if (!list || !list->content)
		perror_exit("ft_lstnew failed @asterisk_process");
	ft_lstadd_front(&list_names, list);
	list = list_names;
	while (list)
	{
		asterisk_proc_list(list);
		list = list->next;
	}
	if (add_tokens(tok, list_names))
	{
		if (tok->prev)
			tok->prev->next = tok->next;
		else
			m->token_start = tok->next;
		if (tok->next)
			tok->next->prev = tok->prev;
		free(tok->str);
		free(tok);
	}
	ft_lstclear(&list_names, free);
}

// bonus asterisk

void	asterisk_expand(t_meta *m)
{
	t_token	*ct;
	t_token	*tmp;
	char	*asp;

	ct = m->token_start;
	while (ct)
	{
		tmp = ct->next;
		if (find_ast(ct->str))
			asterisk_process(m, ct);
		ct = tmp;
	}
}