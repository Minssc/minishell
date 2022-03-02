/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstins_front.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/11 20:16:58 by minsunki          #+#    #+#             */
/*   Updated: 2021/08/03 15:22:46 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_dlstins_front(t_dlist **lst, t_dlist *new)
{
	if (!new || !lst)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		new->prev = (*lst)->prev;
		new->next = *lst;
		if ((*lst)->prev)
			(*lst)->prev->next = new;
		(*lst)->prev = new;
	}
}
