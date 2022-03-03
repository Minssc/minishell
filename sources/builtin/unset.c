/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:52:23 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/03 16:43:29 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 매개변수 root 는 반드시 존재하는 값으로 들어와야 함.
// cur_ptr 은 root 리스트의 노드 주소(NULL 포함)여야 함.
// cf. cur_ptr == NULL 이면, 마지막 노드 반환
// cf. cur_ptr 이 첫 노드라면 prev = NULL 반환
t_list	*find_prev_node(t_list *root, t_list *cur_ptr)
{
	t_list	*cur;
	t_list	*prev;

	if (!root)
		perror_exit("root is NULL @find_prev_node");
	if (!cur_ptr)
		return (ft_lstlast(root));
	cur = root;
	prev = NULL;
	while (cur)
	{
		if (cur == cur_ptr)
			break ;
		prev = cur;
		cur = cur->next;
	}
	if (cur == root)
		return (NULL);
	if (!cur && prev == ft_lstlast(root))
		perror_exit("Invalid input: cur_ptr @find_prev_node");
	return (prev);
}

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
