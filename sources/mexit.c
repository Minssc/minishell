/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mexit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:52:36 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/10 23:01:43 by tjung            ###   ########.fr       */
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
		printf("minishell: exit: User defined exit\n");
	else
		printf("minishell: exit: %s\n", strerror(ec));
	mexit(ec);
}

void	mexit_cm(char *str, int ec)
{
	printf("%s\n", str);
	mexit(ec);
}

void	perror_exit(char *str)
{
	ft_putendl_fd("Error", STDERR_FILENO);
	ft_putendl_fd(str, STDERR_FILENO);
	mexit_pe(255);
}
