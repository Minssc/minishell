/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 20:08:19 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/09 22:40:56 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_add_back(t_token **th, t_token *nt)
{
	t_token	*prev;

	if (!*th)
		*th = nt;
	else
	{
		prev = *th;
		while (prev && prev->next)
			prev = prev->next;
		prev->next = nt;
		nt->prev = prev;
	}
}

void	token_destroy(t_meta *m)
{
	t_token	*tok;
	t_token *tmp;

	tok = m->token_start;
	while (tok)
	{
		tmp = tok->next;
		free(tok->str);
		free(tok);
		tok = tmp;
	}
	m->token_start = 0;
}

void	token_parse(t_meta *m, char *from, char *to)
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
	token_add_back(&m->token_start, nt);
	token_ident(nt);
}
