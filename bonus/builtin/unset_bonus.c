/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:52:23 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/12 12:03:05 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

// keys[0] = unset 명령어
int	builtin_unset(char **keys)
{
	t_meta	*m;
	t_list	*target;
	t_list	*prev;
	int		i;

	m = meta_get();
	i = 0;
	while (keys[++i])
	{
		target = env_find(m, keys[i]);
		if (target)
		{
			prev = find_prev_node(m->list_env, target);
			if (prev)
				prev->next = target->next;
			else
				m->list_env = target->next;
			ft_lstdelone(target, free);
		}
	}
	m->exit_status = 0;
	return (0);
}
