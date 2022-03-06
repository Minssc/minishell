/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:46:17 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/07 02:18:59 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	quotes(char *line)
{
	int		flag;

	flag = 0;
	while (*line)
	{
		if (*line == '\'')
			flag ^= 0b01;
		else if (*line == '\"')
			flag ^= 0b10;
		line++;
	}
	return (flag);
}

static void	loop_start(t_meta *m)
{
	while (1)
	{
		m->line = readline("minishell$ ");
		if (!m->line)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			mexit(0);
		}
		if (ms_isemptystr(m->line))
		{
			ms_free((void **)(&m->line));
			continue ;
		}
		// if (quotes(str))
		// 	continue ;
		add_history(m->line);
		token_destroy(m);
		parse(m, m->line);
		// 파싱에 문제가 없는 경우
		// 명령어 실행 혹은 에러(예외)처리
		exec_start(m);
		ms_free((void **)(&m->line));
	}
}

int	main(int argc, char *argv[] __attribute__((unused)), char *envp[])
{
	t_meta		*m;

	if (argc > 1)
	{
		printf("too many arguments\n");
		return (0);
	}
	m = meta_init();
	m->stdin = dup(STDIN_FILENO);
	m->stdout = dup(STDOUT_FILENO);
	env_init(m, envp);
	set_signal();
	loop_start(m);
	return (0);
}
