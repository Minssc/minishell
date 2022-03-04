/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:52:53 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/03 12:24:28 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sighandl(int signum)
{
	if (signum == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	else if (signum == SIGQUIT)
	{
		//TODO kill child?
	}
}

int	ms_loop(t_meta *m)
{
	char	*line;

	signal(SIGINT, sighandl);
	signal(SIGQUIT, sighandl);
	while (1)
	{
		line = readline("minishell$ ");
		if (line)
		{
			printf("readline: %s\n", line);
			parse(m, line);
			free(line);
		}
		else
		{
			printf("exit\n");
			exit(0);
		}
	}
	return (0);
}
