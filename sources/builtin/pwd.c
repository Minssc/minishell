/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:52:17 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/02 17:56:39 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mini_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		g_exit_status = 1;
		return (1);
	}
	ft_putendl_fd(path, STDOUT_FILENO);
	free(path);
	g_exit_status = 0;
	return (0);
}
