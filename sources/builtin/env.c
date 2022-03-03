/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:51:59 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/04 03:52:46 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(char **argu)
{
	t_meta	*m;
	t_list	*cur;

	m = meta_get();
	if (argu[1])
	{
		m->exit_status = 1;
		ft_putendl_fd("env: too many arguments", STDERR_FILENO);
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
