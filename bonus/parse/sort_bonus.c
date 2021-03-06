/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 01:00:38 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/12 12:03:05 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

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

void	sort_tokens(t_meta *m)
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
