/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dlstmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 18:56:21 by minsunki          #+#    #+#             */
/*   Updated: 2021/08/03 15:22:49 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_dlist	*ft_dlstmap(t_dlist *lst, void *(*f)(void *), void (*del)(void *))
{
	t_dlist	*ret;
	t_dlist	*tmp;

	if (!f)
		return (0);
	ret = 0;
	while (lst)
	{
		tmp = ft_dlstnew((*f)(lst->content));
		if (!tmp)
		{
			ft_dlstclear(&ret, del);
			return (0);
		}
		ft_dlstadd_back(&ret, tmp);
		lst = lst->next;
	}
	return (ret);
}
