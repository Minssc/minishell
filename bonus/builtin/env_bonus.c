/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:51:59 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/12 12:03:05 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	builtin_env(char **argu)
{
	t_meta	*m;
	t_list	*cur;

	m = meta_get();
	if (argu[1])
	{
		m->exit_status = 1;
		ms_puterr(argu[0], EM_TOO_MANY_ARGS);
		return (1);
	}
	cur = m->list_env;
	while (cur)
	{
		ft_putendl_fd((char *)cur->content, STDOUT_FILENO);
		cur = cur->next;
	}
	m->exit_status = 0;
	return (0);
}
