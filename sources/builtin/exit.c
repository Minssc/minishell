/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:52:06 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/11 18:01:29 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_rpipe_location(t_meta *m)
{
	t_token	*ct;
	t_token	*et;

	ct = m->token_start;
	et = NULL;
	while (ct)
	{
		if (!ft_strcmp(ct->str, "exit"))
		{
			et = ct->next;
			while (et)
			{
				if (et->type == T_PIP)
					return (1);
				et = et->next;
			}
		}
		ct = ct->next;
	}
	return (0);
}

static void	do_exit(int is_pip, int es, char *arg, int opt)
{
	t_meta	*m;

	m = meta_get();
	if ((!m->child && !is_pip) || (m->child && !is_pip))
	{
		m->exit_status = es;
		if (!m->child)
			ft_putendl_fd("exit", STDERR_FILENO);
		if (opt == 3)
			ms_puterr(arg, EM_TOO_MANY_ARGS);
		else if (opt == 4)
			ms_puterr(arg, EM_NUMERIC_REQUIR);
		if (opt != 3)
			mexit(m->exit_status);
	}
}

static void	sub_builtin_exit(t_meta *m, char *arg, int opt)
{
	int	is_pip;

	is_pip = check_rpipe_location(m);
	if (opt == 1)
		do_exit(is_pip, 0, NULL, 1);
	else if (opt == 2)
		do_exit(is_pip, ft_atoi(arg) % 256, NULL, 2);
	else if (opt == 3)
		do_exit(is_pip, 1, arg, 3);
	else if (opt == 4)
		do_exit(is_pip, 2, arg, 4);
}

void	builtin_exit(char **exit_cmd)
{
	t_meta	*m;
	int		idx;

	m = meta_get();
	idx = 0;
	while (exit_cmd[idx])
		idx++;
	if (idx == 1)
		sub_builtin_exit(m, NULL, 1);
	else if (idx == 2 && ft_isnumstr(exit_cmd[1]))
		sub_builtin_exit(m, exit_cmd[1], 2);
	else if (idx > 2 && ft_isnumstr(exit_cmd[1]))
		sub_builtin_exit(m, exit_cmd[1], 3);
	else if (!ft_isnumstr(exit_cmd[1]))
		sub_builtin_exit(m, exit_cmd[1], 4);
}
