/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mexit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:52:36 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/02 13:46:26 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mexit(int ec)
{
	meta_destroy();
	exit(ec);
}

void	perror_exit(char *str)
{
	printf("Error\n%s\n",str);
	mexit(1);
}