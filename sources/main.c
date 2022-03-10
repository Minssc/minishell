/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:46:17 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/10 22:27:55 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	quotes(char *line)
{
	int		flag;

	flag = 0;
	while (*line)
	{
		if (!flag && *line == '\\' && (*(line + 1) == '\''
				|| *(line + 1) == '\"'))
			line += 2;
		if ((flag & Q_SQ) && *line == '\'')
			flag ^= Q_SQ;
		else if (flag & Q_DQ)
		{
			if (*line == '\\' && *(line + 1) == '\"')
				line++;
			else if (*line == '\"')
				flag ^= Q_DQ;
		}
		else if (!(flag & Q_SQ) && *line == '\'')
			flag ^= Q_SQ;
		else if (!(flag & Q_DQ) && *line == '\"')
			flag ^= Q_DQ;
		line++;
	}
	return (flag);
}

static void	sub_loop(t_meta *m)
{
	add_history(m->line);
	parse(m, m->line);
	exec_start(m);
	token_destroy(m);
	ms_free((void **)(&m->rl_msg));
	ms_free((void **)(&m->line));
}

static void	loop_start(t_meta *m)
{
	while (1)
	{
		rl_set_message(m);
		m->line = readline(m->rl_msg);
		if (!m->line)
		{
			ft_putendl_fd("exit", STDERR_FILENO);
			mexit(0);
		}
		if (ms_isemptystr(m->line))
		{
			ms_free((void **)(&m->line));
			continue ;
		}
		if (quotes(m->line))
		{
			ms_puterr(ET_SYNTAX, EM_UNEXPECTED_EOF);
			ms_free((void **)(&m->line));
			continue ;
		}
		sub_loop(m);
	}
}

int	main(int argc, char *argv[] __attribute__((unused)), char *envp[])
{
	t_meta	*m;

	if (argc > 1)
	{
		ms_puterr(ET_SYNTAX, EM_TOO_MANY_ARGS);
		return (0);
	}
	m = meta_init();
	m->stdin = dup(STDIN_FILENO);
	m->stdout = dup(STDOUT_FILENO);
	fd_reset(m);
	env_init(m, envp);
	set_signal();
	loop_start(m);
	return (0);
}
