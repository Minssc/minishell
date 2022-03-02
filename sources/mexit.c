/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mexit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:52:36 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/03 01:20:49 by minsunki         ###   ########seoul.kr  */
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
	printf("%s\n",str);
	mexit(ec);
}

void	perror_exit(char *str)
{
	printf("Error\n%s\n",str);
	mexit_pe(255);
}
