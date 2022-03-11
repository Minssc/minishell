/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 15:26:28 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/11 17:04:07 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_fderror(t_meta *m, char *tstr, int isamb)
{
	ms_set_es(m, 1);
	m->stop = 1;
	if (isamb)
		ms_puterr("", "ambiguous redirect");
	else
		ms_puterr(tstr, strerror(errno));
}

void	redir_r(t_meta *m, t_token *tok, t_byte type)
{
	if (tok->type == T_EMP)
	{
		redir_fderror(m, "", 1);
		return ;
	}
	fd_close(m->fd_out);
	if (type == T_RDR)
		m->fd_out = open(tok->str, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR
				| S_IWUSR | S_IRGRP | S_IROTH);
	else
		m->fd_out = open(tok->str, O_CREAT | O_WRONLY | O_APPEND, S_IRUSR
				| S_IWUSR | S_IRGRP | S_IROTH);
	if (m->fd_out < 0)
		redir_fderror(m, tok->str, 0);
	else
		dup2(m->fd_out, STDOUT_FILENO);
}

void	redir_l(t_meta *m, t_token *tok, t_byte type)
{
	if (tok->type == T_EMP)
	{
		redir_fderror(m, "", 1);
		return ;
	}
	if (type == T_RDL)
	{
		fd_close(m->fd_in);
		m->fd_in = open(tok->str, O_RDONLY, S_IRWXU);
		if (m->fd_in < 0)
			redir_fderror(m, tok->str, 0);
		else
			dup2(m->fd_in, STDIN_FILENO);
	}
	else
		heredoc_open(m);
}

static void	child_setup(t_meta *m)
{
	fd_close(m->pipe[1]);
	dup2(m->pipe[0], STDIN_FILENO);
	m->pipe[1] = -1;
	m->child = 1;
	m->stop = 0;
	if (m->fd_out != -1)
	{
		fd_close(m->fd_out);
		m->fd_out = -1;
		dup2(m->stdout, STDOUT_FILENO);
	}
}

int	redir_p(t_meta *m)
{
	pipe(m->pipe);
	m->pid = fork();
	if (m->pid == 0)
	{
		child_setup(m);
		return (2);
	}
	else
	{
		fd_close(m->pipe[0]);
		m->pipe[0] = -1;
		if (m->fd_out != -1)
			return (1);
		dup2(m->pipe[1], STDOUT_FILENO);
		m->fd_out = m->pipe[1];
		return (1);
	}
}
