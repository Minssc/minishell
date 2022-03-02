/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_queue.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 23:37:23 by minsunki          #+#    #+#             */
/*   Updated: 2021/08/03 15:23:16 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_qpush(t_que *q, void *v)
{
	t_dlist	*new;

	new = ft_dlstnew(v);
	ft_dlstadd_front(&q->tail, new);
	if (!q->size++)
		q->head = q->tail;
}

void	ft_qpop(t_que *q)
{
	t_dlist	*tmp;

	if (!q->size || !q->head)
		return ;
	tmp = q->head->prev;
	ft_dlstdelone(q->head, free);
	q->head = tmp;
	if (!(--(q->size)))
		q->tail = 0;
}

void	*ft_qtop(t_que *q)
{
	if (!q->head)
		return (0);
	return (q->head->content);
}

int	ft_qempty(t_que *q)
{
	return (!q->size);
}

int	ft_qsize(t_que *q)
{
	return (q->size);
}
