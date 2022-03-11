/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mexit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:52:36 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/11 11:15:21 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mexit(int ec)
{
	meta_destroy();
	exit(ec);
}

void	mexit_pe(int ec)
{
	if (ec == 255)
		ft_putendl_fd("minishell: exit: User defined exit", STDERR_FILENO);
	else
	{
		ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
		ft_putendl_fd(strerror(ec), STDERR_FILENO);
	}
	mexit(ec);
}

void	mexit_cm(char *str, int ec)
{
	ft_putendl_fd(str, STDERR_FILENO);
	mexit(ec);
}

void	perror_exit(char *str)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	mexit_pe(255);
}
