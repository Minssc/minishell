/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 22:24:00 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/05 15:26:18 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO 대소문자 구분 해야하나?

static t_token	*next_cmd(t_token *tok)
{
	while (tok)
	{
		if (token_ident(tok) == T_CMD)
			return (tok);
		tok = tok->next;
	}
	return (0);
}

static int	is_builtin(char *bin)
{
	if (ft_strcmp(bin, "cd") == 0)
		return (B_CD);
	else if (ft_strcmp(bin, "echo") == 0)
		return (B_ECHO);
	else if (ft_strcmp(bin, "env") == 0)
		return (B_ENV);
	else if (ft_strcmp(bin, "exit") == 0)
		return (B_EXIT);
	else if (ft_strcmp(bin, "export") == 0)
		return (B_EXPT);
	else if (ft_strcmp(bin, "pwd") == 0)
		return (B_PWD);
	else if (ft_strcmp(bin, "unset") == 0)
		return (B_UNST);
	else
		return (0);
}

static void	execute_builtin(t_meta *m, int flag)
{
	printf("run a builtin! BI flag: %d\n",flag);
}

static int	execute_bin(t_meta *m)
{
	char	*bin;
	int		ret;

	ret = 0;
	bin = bin_find(m, m->argv[0]);
	if (!bin)
		return (1); // TODO MANAGE ERROR CODES. FILE NOT FOUND
	ret = bin_run(m, bin);
}

static void	execute(t_meta *m, t_token *tok)
{
	int	bi;

	bi = is_builtin(m->argv[0]);
	if (bi)
		execute_builtin(m, bi);
	else
		execute_bin(m);
}

void	exec_start(t_meta *m)
{
	t_token	*ct;

	ct = next_cmd(m->token_start);
	while (ct)
	{
		m->argv = argv_build(ct);
		execute(m, ct);
		argv_destroy(m);
		ct = next_cmd(ct->next);
	}
}