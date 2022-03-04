/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 22:24:00 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/04 20:18:46 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*next_cmd(t_token *tok)
{
	while (tok)
	{
		if (token_ident(tok) == T_CMD)
			return (tok);
		tok = tok->next;
	}
	return (0);
}

static void	execute(t_meta *m, t_token *tok)
{
	execute_bin(m);
}

void	exec_start(t_meta *m)
{
	t_token	*ct;

	ct = next_cmd(m->token_start);
	while (ct)
	{
		m->argv = argv_build(ct);
		execute(m, ct);
		argv_destroy(m);
		ct = next_cmd(ct->next);
	}
}