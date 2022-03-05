/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 20:08:19 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/04 17:20:48 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_byte	token_ident(t_token *tok)
{
	if (ft_strncmp(tok->str, "|", 1) == 0)
		tok->type = T_PIP;
	else if (ft_strncmp(tok->str, "<<", 2) == 0)
		tok->type = T_APL;
	else if (ft_strncmp(tok->str, ">>", 2) == 0)
		tok->type = T_APR;
	else if (ft_strncmp(tok->str, "<", 1) == 0)
		tok->type = T_RDL;
	else if (ft_strncmp(tok->str, ">", 1) == 0)
		tok->type = T_RDR;
	else if (!tok->prev || (tok->prev->type & 0b11111100))
		tok->type = T_CMD;
	else
		tok->type = T_ARG;
	return (tok->type);
}

void	token_ident_all(t_meta *m)
{
	t_token	*ct;

	ct = m->token_start;
	while (ct)
	{
		ct->type = T_EMP;
		token_ident(ct);
		ct = ct->next;
	}
}

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

void	token_del(t_token *tok)
{
	t_token *prev;
	t_token *next;

	if (!tok)
		return ;
	prev = tok->prev;
	next = tok->next;
	if (prev)
		prev->next = next;
	if (next)
		next->prev = prev;
	if (tok->str)
		free(tok->str);
	free(tok);
}