/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 21:39:21 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/07 16:42:02 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fd_close(int fd)
{
	if (fd > 0)
		close(fd);
}

void	fd_reset(t_meta *m)
{
	m->fd_in = -1;
	m->fd_out = -1;
}

void	fd_destroy(t_meta *m)
{
	fd_close(m->fd_in);
	fd_close(m->fd_out);
}

void	fd_reset_std(t_meta *m)
{
	dup2(m->stdin, STDIN_FILENO);
	dup2(m->stdout, STDOUT_FILENO);
}