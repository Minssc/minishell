/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 01:19:12 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/07 01:31:41 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// if token type is delim, do not update the type.

t_byte	token_ident(t_token *tok)
{
	t_byte	nt;

	nt = T_EMP;
	if (ft_strcmp(tok->str, "|") == 0)
		nt = T_PIP;
	else if (ft_strcmp(tok->str, "<<") == 0)
		nt = T_APL;
	else if (ft_strcmp(tok->str, ">>") == 0)
		nt = T_APR;
	else if (ft_strcmp(tok->str, "<") == 0)
		nt = T_RDL;
	else if (ft_strcmp(tok->str, ">") == 0)
		nt = T_RDR;
	else if (!tok->prev || (tok->prev->type & DELIM))
		nt = T_CMD;
	else
		nt = T_ARG;
	if (tok->type && (nt & DELIM))
		 ;
	else
		tok->type = nt;
	return (tok->type);
}

t_token	*token_next_delim(t_token *tok)
{
	t_token	*ret;

	if (!tok)
		return (0);
	ret = tok->next;
	while (ret)
	{
		if (ret->type & DELIM)
			return (ret);
		ret = ret->next;
	}
	return (ret);
}

t_token	*token_prev_delim(t_token *tok)
{
	t_token	*ret;

	if (!tok)
		return (0);
	ret = tok->prev;
	while (ret)
	{
		if (ret->type & DELIM)
			return (ret);
		ret = ret->prev;
	}
	return (ret);
}

// TODO remove this?
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
