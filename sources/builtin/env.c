/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:51:59 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/03 13:43:45 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(void)
{
	t_meta	*m;
	t_list	*cur;

	m = meta_get();
	cur = m->list_env;
	while (cur)
	{
		ft_putendl_fd((char *)cur->content, STDOUT_FILENO);
		cur = cur->next;
	}
	m->exit_status = 0;
	return (0);
}
