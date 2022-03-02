/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:51:59 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/02 17:48:25 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_env(t_env *root)
{
	t_env	*curr;

	curr = root;
	while (curr)
	{
		ft_putendl_fd(curr->contents, STDOUT_FILENO);
		curr = curr->next;
	}
	g_exit_status = 0;
	return (0);
}
