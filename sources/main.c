/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:46:17 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/04 20:16:52 by minsunki         ###   ########seoul.kr  */
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
	char	*str;

	while (1)
	{
		str = readline("minishell$ ");
		if (!str)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			mexit(0);
		}
		if (ms_isemptystr(str))
		{
			free(str);
			continue ;
		}
		if (quotes(str))
			continue ;
		add_history(str);
			
		m->token_start = 0;
		parse(m, str);
		// 파싱에 문제가 없는 경우
		// 명령어 실행 혹은 에러(예외)처리
		exec_start(m);
		free(str);
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
	// m->in = dup(stdin);
	// m->out = dup(stdout);
	env_init(m, envp);
	set_signal();
//	loop_start(m);
	return (0);
}
