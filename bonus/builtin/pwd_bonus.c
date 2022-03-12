/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:52:17 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/12 12:03:05 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	builtin_pwd(void)
{
	t_meta	*m;
	char	*path;

	m = meta_get();
	path = getcwd(NULL, 0);
	if (!path)
		perror_exit("getcwd failed @builtin_pwd");
	ft_putendl_fd(path, STDOUT_FILENO);
	free(path);
	m->exit_status = 0;
	return (0);
}
