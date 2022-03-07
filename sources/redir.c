/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 15:26:28 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/07 22:55:53 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redir_r(t_meta *m, t_token *tok, t_byte type)
{
	fd_close(m->fd_out);
	if (type == T_RDR)
		m->fd_out = open(tok->str, O_CREAT | O_WRONLY | O_TRUNC, S_FLAG);
	else
		m->fd_out = open(tok->str, O_CREAT | O_WRONLY | O_APPEND, S_FLAG);
	if (m->fd_out < 0)
	{
		ms_puterr(tok->str, EM_NO_SUCH_FILE_DIR);
		m->stop = 1;
		m->exit_status = 1;
		return ;
	}
	dup2(m->fd_out, STDOUT_FILENO);
}

void	redir_l(t_meta *m, t_token *tok, t_byte type)
{
	if (type == T_RDL)
	{
		fd_close(m->fd_in);
		m->fd_in = open(tok->str, O_RDONLY, S_IRWXU);
		if (m->fd_in < 0)
		{
			ms_puterr(tok->str,EM_NO_SUCH_FILE_DIR);
			m->stop = 1;
			m->exit_status = 1;
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
		m->child = 1;
		m->stop = 0;
		return (2);
	}
	else
	{
		fd_close(pfd[0]);
		if (m->fd_out != -1)
			return (1);
		dup2(pfd[1], STDOUT_FILENO);
		m->fd_out = pfd[1];
		return (1);
	}
}
