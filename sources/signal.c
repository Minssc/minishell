/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 13:23:14 by tjung             #+#    #+#             */
/*   Updated: 2022/03/10 23:01:50 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ctrl-\ = 3 ctrl-c = 2

void	sig_handler(int signum)
{
	t_meta	*m;

	m = meta_get();
	write(STDOUT_FILENO, "\n", 1);
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
