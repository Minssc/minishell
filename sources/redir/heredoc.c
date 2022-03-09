/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 01:13:38 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/09 12:40:40 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	readdoc(t_meta *m, t_token *tok, char *hname)
{
	int		fd;

	fd = open(hname, O_CREAT | O_WRONLY | O_TRUNC, S_FLAG);
	if (fd < 0)
	{
		ms_puterr(hname, strerror(errno));
		m->stop = 1;
		ms_set_es(m, 1);
		return ;		
	}
	heredoc_read(m, tok->str, fd);
	fd_close(fd);
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
