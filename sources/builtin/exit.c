/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:52:06 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/04 03:41:41 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_exit(char **exit_cmd)
{
	t_meta	*m;
	int		idx;

	m = meta_get();
	idx = 0;
	while (exit_cmd[idx])
		idx++;
	if (idx == 1)
		m->exit_status = 0;
	else if (idx == 2 && ft_isnumstr(exit_cmd[1]))
		m->exit_status = ft_atoi(exit_cmd[1]) % 256;
	else if (idx > 2 && ft_isnumstr(exit_cmd[1]))
	{
		m->exit_status = 1;
		ft_putendl_fd("exit: too many arguments", STDERR_FILENO);
		return ;
	}
	else
		m->exit_status = 255;
	ft_putendl_fd("exit", STDOUT_FILENO);
	mexit(m->exit_status);
}
