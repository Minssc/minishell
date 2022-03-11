/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:52:06 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/11 13:46:31 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	sub_builtin_exit_perror(int idx, int is_num, char *arg)
{
	if (idx == 2 && is_num)
		ft_putendl_fd("exit", STDOUT_FILENO);
	else
	{
		ft_putendl_fd("exit", STDERR_FILENO);
		if (!is_num)
			ms_puterr(arg, EM_NUMERIC_REQUIR);
		else
		{
			ms_puterr(arg, EM_TOO_MANY_ARGS);
			return (0);
		}
	}
	return (1);
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
	{
		m->exit_status = 0;
		ft_putendl_fd("exit", STDOUT_FILENO);
		mexit(m->exit_status);
	}
	else if (idx == 2 && ft_isnumstr(exit_cmd[1]))
		m->exit_status = ft_atoi(exit_cmd[1]) % 256;
	else if (idx > 2 && ft_isnumstr(exit_cmd[1]))
		m->exit_status = 1;
	else if (!ft_isnumstr(exit_cmd[1]))
		m->exit_status = 2;
	else
		m->exit_status = 255;
	if (!sub_builtin_exit_perror(idx, ft_isnumstr(exit_cmd[1]), exit_cmd[1]))
		return ;
	mexit(m->exit_status);
}
