/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:46:17 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/03 00:53:42 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	cp_envp_lst(t_info *info, char **envp)
// {
// 	t_env	*curr;
// 	int		size;
// 	int		i;

// 	size = 0;
// 	while (envp[size])
// 		++size;
// 	i = -1;
// 	while (++i < size)
// 		ft_lstadd_back_env(&info->n_env, ft_lstnew_env());
// 	curr = info->n_env;
// 	i = -1;
// 	while (curr)
// 	{
// 		curr->contents = ft_strdup(envp[++i]);
// 		curr = curr->next;
// 	}
// 	return (0);
// }

static void	loop_start(t_meta *m)
{
	char	*str;
	while (1)
	{
		// info->input = readline("minishell: ");
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
	// t_info	info;

	if (argc > 1)
	{
		printf("too many arguments\n");
		return (0);
	}
	m = meta_init();
	// ft_memset(&info, 0, sizeof(info));
	// cp_envp_lst(m, envp);
	env_init(m, envp);
	set_signal();
	loop_start(m);
	return (0);
}
