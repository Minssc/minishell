/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 22:24:00 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/12 13:36:14 by minsunki         ###   ########seoul.kr  */
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

static void	execute_bin(t_meta *m)
{
	char	*bin;
	char	*lc_cmd;
	int		ret;

	ret = 0;
	lc_cmd = ft_strdup(m->argv[0]);
	lc_cmd = ms_tolower(lc_cmd);
	if (ft_strlen(lc_cmd))
	{
		bin = bin_find(m, lc_cmd);
		if (!bin)
			ret = bin_run(m, lc_cmd);
		else
		{
			ret = bin_run(m, bin);
			free(bin);
		}
	}
	free(lc_cmd);
	ms_set_es(m, ret);
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
		piped = redir_p(m);
	if (nt && piped != 1)
		execute(m, exec_next(nt));
	if (piped != 1 && !nt)
		m->is_last = 1;
	if ((!pt || (pt->type & T_PIP)) && piped != 1 && !m->stop)
		exec_cmd(m, tok);
}

void	exec_start(t_meta *m)
{
	t_token	*ct;
	int		stat;

	stat = 0;
	m->stop = 0;
	m->hd_cur = 0;
	m->is_last = 0;
	if (!m->token_start)
		return ;
	ct = next_cmd(m->token_start);
	if (!ct)
		return ;
	execute(m, ct);
	fd_reset_std(m);
	fd_destroy(m);
	fd_reset(m);
	waitpid(-1, &stat, 0);
	if (!m->is_last)
		ms_set_es(m, WEXITSTATUS(stat));
	if (m->child)
		mexit(m->exit_status);
}
