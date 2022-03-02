/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstadd_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:54:58 by minsunki          #+#    #+#             */
/*   Updated: 2021/08/03 15:22:42 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstadd_back(t_dlist **lst, t_dlist *new)
{
	t_dlist	*t;

	if (!new || !lst)
		return ;
	t = ft_dlstlast(*lst);
	if (!t)
		*lst = new;
	else
	{
		t->next = new;
		new->prev = t;
	}
}
