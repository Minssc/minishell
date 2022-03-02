/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstclear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:55:24 by minsunki          #+#    #+#             */
/*   Updated: 2021/08/03 15:22:43 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	dprev(t_dlist *lst, void (*del)(void *))
{
	t_dlist	*tmp;

	while (lst)
	{
		tmp = lst->prev;
		ft_dlstdelone(lst, del);
		lst = tmp;
	}
}

static void	dnext(t_dlist *lst, void (*del)(void *))
{
	t_dlist	*tmp;

	while (lst)
	{
		tmp = lst->next;
		ft_dlstdelone(lst, del);
		lst = tmp;
	}
}

void	ft_dlstclear(t_dlist **lst, void (*del)(void *))
{
	if (!del || !lst || !*lst)
		return ;
	dprev((*lst)->prev, del);
	dnext((*lst)->next, del);
	ft_dlstdelone(*lst, del);
	*lst = 0;
}
