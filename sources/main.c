/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:46:17 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/02 18:51:59 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char **environ;

int	main(int argc, char *argv[])
{
	t_meta *m;

	char	**test = environ;
	while (*test)
	{
		printf("%s\n",*test);
		test++;
	}

	m = meta_init();
	ms_loop(m);
	meta_destroy();
	return (0);
}