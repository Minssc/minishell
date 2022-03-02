/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstins_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 20:30:04 by minsunki          #+#    #+#             */
/*   Updated: 2021/08/03 15:22:46 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstins_back(t_dlist **lst, t_dlist *new)
{
	if (!new || !lst)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		new->next = (*lst)->next;
		new->prev = *lst;
		if ((*lst)->next)
			(*lst)->next->prev = new;
		(*lst)->next = new;
	}
}
