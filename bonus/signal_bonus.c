/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 13:23:14 by tjung             #+#    #+#             */
/*   Updated: 2022/03/12 12:03:05 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

//ctrl-\ = 3 ctrl-c = 2

void	sig_handler(int signum)
{
	t_meta	*m;

	m = meta_get();
	write(STDOUT_FILENO, "\n", 1);
	ms_set_es(m, 130);
	if (!m->waiting && signum == SIGINT)
	{
		if (rl_on_new_line() == -1)
			mexit(1);
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	set_signal(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}
