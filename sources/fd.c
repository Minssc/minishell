/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 21:39:21 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/10 23:01:32 by tjung            ###   ########.fr       */
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
	m->pipe[0] = -1;
	m->pipe[1] = -1;
}

void	fd_destroy(t_meta *m)
{
	fd_close(m->fd_in);
	fd_close(m->fd_out);
	fd_close(m->pipe[0]);
	fd_close(m->pipe[1]);
}

void	fd_reset_std(t_meta *m)
{
	dup2(m->stdin, STDIN_FILENO);
	dup2(m->stdout, STDOUT_FILENO);
}
