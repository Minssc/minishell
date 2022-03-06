/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 15:26:28 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/07 00:42:12 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// REDIRECTIONS

void	redir_r(t_meta *m, t_token *tok, t_byte type)
{
	fd_close(m->fd_out);
	if (type == T_RDR)
		m->fd_out = open(tok->str, O_CREAT | O_WRONLY | O_TRUNC, S_FLAG);
	else
		m->fd_out = open(tok->str, O_CREAT | O_WRONLY | O_APPEND, S_FLAG);
	if (m->fd_out < 0)
	{
		// TODO file not found?
		m->stop = 1;
		return ;
	}
	dup2(m->fd_out, STDOUT_FILENO);
}

static void	readdoc(t_meta *m, t_token *tok)
{
	int		fd;
	char	*inp;
	char	*exp;

	fd = open(HEDOC, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	while (1)
	{
		inp = readline("> ");
		if (!inp || !ft_strcmp(tok->str, inp))
			break ;
		exp = find_e(inp);
		while (exp)
		{
			insert_env(m, &inp, &exp);
			exp = find_e(inp);
		}
		ft_putendl_fd(inp, fd);
		ms_free((void **)&inp);
	}
	ms_free((void **)&inp);
	fd_close(fd);
}

static void	heredoc(t_meta *m, t_token *tok)
{
	int		last_hdoc;

	last_hdoc = 1;
	readdoc(m, tok);
	// ft_putendl_fd("HEREDOC",STDERR_FILENO);
	while (tok)
	{
		if (tok->type == T_APL)
			last_hdoc = 0;
		if (tok->type == T_PIP)
			break ;
		tok = tok->next;
	}
	if (!last_hdoc)
		return ;
	fd_close(m->fd_in);
	m->fd_in = open(HEDOC, O_RDONLY, S_IRWXU);
	dup2(m->fd_in, STDIN_FILENO);
}

void	redir_l(t_meta *m, t_token *tok, t_byte type)
{
	if (type == T_RDL)
	{
		fd_close(m->fd_in);
		m->fd_in = open(tok->str, O_RDONLY, S_IRWXU);
		if (m->fd_in < 0)
		{
			// TODO file not found?
			m->stop = 1;
			return ;
		}
		dup2(m->fd_in, STDIN_FILENO);
	}
	else
		heredoc(m, tok);
}

int	redir_p(t_meta *m, t_token *tok)
{
	int	pfd[2];

	pipe(pfd);
	m->pid = fork();
	if (m->pid == 0)
	{
		fd_close(pfd[1]);
		dup2(pfd[0], STDIN_FILENO);
		m->fd_in = pfd[0];
		m->stop = 0;
		return (2);
	}
	else
	{
		fd_close(pfd[0]);
		dup2(pfd[1], STDOUT_FILENO);
		m->fd_out = pfd[1];
		m->child = 1;
		return (1);
	}
}
