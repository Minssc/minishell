/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 12:31:40 by tjung             #+#    #+#             */
/*   Updated: 2022/03/02 16:12:06 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstnew_env(void)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	ft_memset(new, 0, sizeof(*new));
	return (new);
}

int	ft_lstsize_env(t_env *lst)
{
	int		size;

	size = 0;
	while (lst != NULL)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}

t_env	*ft_lstlast_env(t_env *lst)
{
	int		size;

	if (lst == NULL)
		return (NULL);
	size = ft_lstsize_env(lst);
	while (--size)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*last;

	if (!(lst) || !(new))
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	last = ft_lstlast_env(*lst);
	last->next = new;
	new->prev = last;
	new->next = NULL;
}

void	ft_lstdelone_env(t_env *lst)
{
	t_env	*tmp_prev;
	t_env	*tmp_next;

	if (!lst)
		return ;
	if (lst->contents)
		free(lst->contents);
	tmp_prev = lst->prev;
	tmp_next = lst->next;
	tmp_prev->next = tmp_next;
	if (tmp_next)
		tmp_next->prev = tmp_prev;
	free(lst);
}
