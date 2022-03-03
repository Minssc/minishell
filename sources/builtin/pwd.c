/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:52:17 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/03 13:38:53 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(void)
{
	t_meta	*m;
	char	*path;

	m = meta_get();
	path = getcwd(NULL, 0);
	if (!path)
	{
		m->exit_status = 1;
		perror_exit("getcwd failed @builtin_pwd");
	}
	ft_putendl_fd(path, STDOUT_FILENO);
	free(path);
	m->exit_status = 0;
	return (0);
}
