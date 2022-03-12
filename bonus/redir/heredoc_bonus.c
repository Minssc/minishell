/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 01:13:38 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/12 12:03:05 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	hdoc_sighandler(int signum)
{
	t_meta	*m;

	m = meta_get();
	(void)signum;
	write(STDOUT_FILENO, "\n", 1);
	fd_close(m->hd_fd);
	m->hd_fd = -1;
	mexit(130);
}

static void	readdoc(t_meta *m, t_token *tok, char *hname)
{
	int	stat;

	signal(SIGINT, SIG_IGN);
	stat = 0;
	m->pid = fork();
	if (m->pid == 0)
	{
		m->hd_fd = open(hname, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR | S_IWUSR
				| S_IRGRP | S_IROTH);
		if (m->hd_fd < 0)
		{
			ms_puterr(hname, strerror(errno));
			mexit(1);
		}
		signal(SIGINT, hdoc_sighandler);
		m->hd_str = tok->str;
		ms_free((void **)&m->line);
		heredoc_read(m);
		fd_close(m->hd_fd);
		mexit(0);
	}
	else
		waitpid(m->pid, &stat, 0);
	ms_set_es(m, WEXITSTATUS(stat));
	set_signal();
}

// tmp 폴더에 minishell_heredoc_# 이름 형식으로 heredoc 문서들 저장

void	heredoc_init(t_meta *m)
{
	t_token	*ct;
	char	*hname;
	int		num;

	num = 0;
	ct = m->token_start;
	while (ct)
	{
		if (ct->type & T_APL)
		{
			hname = heredoc_getname(num++);
			readdoc(m, ct->next, hname);
			free(hname);
		}
		ct = ct->next;
	}
}

void	heredoc_open(t_meta *m)
{
	char	*hname;

	hname = heredoc_getname(m->hd_cur++);
	fd_close(m->fd_in);
	m->fd_in = open(hname, O_RDONLY, S_IRWXU);
	if (m->fd_in < 0)
		redir_fderror(m, hname, 0);
	else
		dup2(m->fd_in, STDIN_FILENO);
	free(hname);
}
