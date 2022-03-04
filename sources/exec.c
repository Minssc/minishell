/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 22:24:00 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/04 17:58:14 by minsunki         ###   ########seoul.kr  */
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

static void	execute(t_meta *m, t_token *tok, char **argv)
{

}

void	exec_start(t_meta *m)
{
	t_token	*ct;

	ct = next_cmd(m->token_start);
	while (ct)
	{
		char **argv = argv_build(ct);
		argv_destroy(argv);
		execute(m, ct, argv);
		ct = next_cmd(ct->next);
	}
	m->token_start = 0;
}