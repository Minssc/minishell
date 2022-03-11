/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:52:06 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/11 21:59:13 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	pipe_exists(t_meta *m)
{
	t_token	*ct;

	ct = m->token_start;
	while (ct)
	{
		if (ct->type == T_PIP)
			return (1);
		ct = ct->next;
	}
	return (0);
}

static void	do_exit(int has_pip, int es, int opt)
{
	t_meta	*m;

	m = meta_get();
	m->exit_status = es;
	if (!m->child && !has_pip)
		ft_putendl_fd("exit", STDERR_FILENO);
	if (opt == 3)
		ms_puterr("exit", EM_TOO_MANY_ARGS);
	else if (opt == 4)
		ms_puterr("exit", EM_NUMERIC_REQUIR);
	if (!m->child && !has_pip && opt != 3)
		mexit(m->exit_status);
}

static void	sub_builtin_exit(t_meta *m, char *arg, int opt)
{
	int	is_pip;

	is_pip = pipe_exists(m);
	if (opt == 1)
		do_exit(is_pip, 0, 1);
	else if (opt == 2)
		do_exit(is_pip, ft_atoi(arg) % 256, 2);
	else if (opt == 3)
		do_exit(is_pip, 1, 3);
	else if (opt == 4)
		do_exit(is_pip, 2, 4);
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
