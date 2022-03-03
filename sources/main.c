/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:46:17 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/03 18:44:20 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	loop_start(t_meta *m)
{
	char	*str;

	while (1)
	{
		str = readline("minishell$ ");
		if (!str)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			exit(0);
		}
		if (ms_isemptystr(str))
		{
			free(str);
			continue ;
		}
		add_history(str);
		parse(m, str);
		// 파싱에 문제가 없는 경우
		// 명령어 실행 혹은 에러(예외)처리
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
	env_init(m, envp);
	set_signal();
//	loop_start(m);
	return (0);
}
