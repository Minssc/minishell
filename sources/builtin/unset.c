/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:52:23 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/02 18:35:11 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*find_key(t_env *root, char *key)
{
	t_env	*curr;
	char	*tmp;
	int		len;

	curr = root;
	tmp = ft_strjoin(key, "=");
	len = ft_strlen(tmp);
	while (curr)
	{
		if (!ft_strncmp(tmp, curr->contents, len + 1))
			break ;
		curr = curr->next;
	}
	free(tmp);
	return (curr);
}

int	mini_unset(t_env *root, char *key)
{
	t_env	*target;

	target = find_key(root, key);
	ft_lstdelone_env(target);
	g_exit_status = 0;
	return (0);
}
