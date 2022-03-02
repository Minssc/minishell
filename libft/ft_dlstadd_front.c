/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:55:13 by minsunki          #+#    #+#             */
/*   Updated: 2021/08/03 15:22:42 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstadd_front(t_dlist **lst, t_dlist *new)
{
	t_dlist		*t;

	if (!new || !lst)
		return ;
	t = ft_dlstfirst(*lst);
	if (!t)
		*lst = new;
	else
	{
		t->prev = new;
		new->next = *lst;
	}
}
