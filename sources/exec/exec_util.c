/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_util.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 01:26:21 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/07 01:26:32 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*next_cmd(t_token *tok)
{
	while (tok)
	{
		if (token_ident(tok) == T_CMD && !(tok->type & (REDIR)))
			return (tok);
		tok = tok->next;
	}
	return (0);
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
