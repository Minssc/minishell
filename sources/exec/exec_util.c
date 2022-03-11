/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 01:26:21 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/11 16:43:58 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*next_cmd(t_token *tok)
{
	while (tok)
	{
		if (token_ident(tok) == T_CMD)
			return (tok);
		tok = tok->next;
	}
	return (0);
}

t_token	*exec_next(t_token *tok)
{
	t_token	*ret;

	ret = 0;
	tok = tok->next;
	while (tok)
	{
		if (!ret && tok->type == T_EMP)
			ret = tok;
		if (tok->type == T_CMD)
			return (tok);
		else if (tok->type & DELIM)
			break ;
		tok = tok->next;
	}
	return (ret);
}

int	is_builtin(char *bin)
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
