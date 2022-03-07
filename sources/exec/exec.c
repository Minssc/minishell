/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 22:24:00 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/07 22:55:06 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_builtin(t_meta *m, int flag)
{
	int		ret;
	
	ret = 0;
	if (flag == B_CD)
		ret = builtin_cd(m->argv);
	else if (flag == B_ECHO)
		ret = builtin_echo(m->argv);
	else if (flag == B_ENV)
		ret = builtin_env(m->argv);
	else if (flag == B_EXIT)
		builtin_exit(m->argv);
	else if (flag == B_EXPT)
		ret = builtin_export(m->argv);
	else if (flag == B_PWD)
		ret = builtin_pwd();
	else if (flag == B_UNST)
		ret = builtin_unset(m->argv);
	return (ret);
}

static int	execute_bin(t_meta *m)
{
	char	*bin;
	int		ret;

	ret = 0;
	bin = bin_find(m, m->argv[0]);
	if (!bin)
		ret = bin_run(m, m->argv[0]);
	else
		ret = bin_run(m, bin);
	m->exit_status = ret;
}

static void	exec_cmd(t_meta *m, t_token *tok)
{
	int	bi;

	if (m->stop)
		return ;
	m->stop = 1;
	m->argv = argv_build(tok);
	bi = is_builtin(m->argv[0]);
	if (bi)
		execute_builtin(m, bi);
	else
		execute_bin(m);
	argv_destroy(m);
}

static void	execute(t_meta *m, t_token *tok)
{
	t_token	*pt;
	t_token	*nt;
	int		piped;

	pt = token_prev_delim(tok);
	nt = token_next_delim(tok);
	piped = 0;
	if (pt && (pt->type & (T_RDR | T_APR)))
		redir_r(m, tok, pt->type);
	else if (pt && (pt->type & (T_RDL | T_APL)))
		redir_l(m, tok, pt->type); 
	else if (pt && (pt->type & T_PIP))
		piped = redir_p(m, tok); 
	if (nt && piped != 1)
		execute(m, nt->next);
	if ((!pt || (pt->type & T_PIP)) && piped != 1 && !m->stop)
		exec_cmd(m, tok);
}

void	exec_start(t_meta *m)
{
	t_token	*ct;
	int		stat;

	m->stop = 0;
	ct = next_cmd(m->token_start);
	execute(m, ct);
	fd_reset_std(m);
	fd_destroy(m);
	fd_reset(m);
	waitpid(-1, &stat, 0);
	if (m->child)
		mexit(stat);
}