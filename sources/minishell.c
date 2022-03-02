/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:52:53 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/02 17:13:52 by minsunki         ###   ########seoul.kr  */
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
			printf("readline: %s\n",line);
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