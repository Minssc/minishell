/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:46:17 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/02 16:32:56 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cp_envp_lst(t_info *info, char **envp)
{
	t_env	*curr;
	int		size;
	int		i;

	size = 0;
	while (envp[size])
		++size;
	i = -1;
	while (++i < size)
		ft_lstadd_back_env(&info->n_env, ft_lstnew_env());
	curr = info->n_env;
	i = -1;
	while (curr)
	{
		curr->contents = ft_strdup(envp[++i]);
		curr = curr->next;
	}
	return (0);
}

void	loop_start(t_info *info)
{
	while (1)
	{
		info->input = readline("minishell: ");
		if (!info->input)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			exit(0);
		}
		if (ft_isspace(info->input))
		{
			free(info->input);
			continue ;
		}
		add_history(info->input);
		// 파싱에 문제가 없는 경우
		// 명령어 실행 혹은 에러(예외)처리
		free(info->input);
	}
}

int	main(int argc, char *argv[] __attribute__((unused)), char *envp[])
{
	t_info	info;

	if (argc > 1)
	{
		printf("too many arguments\n");
		return (0);
	}
	ft_memset(&info, 0, sizeof(info));
	cp_envp_lst(&info, envp);
	set_signal();
	loop_start(&info);
	return (0);
}
