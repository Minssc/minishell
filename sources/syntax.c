/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:42:13 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/11 16:33:41 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_syntax_error(t_token *dt)
{
	ft_putstr_fd("-minishell: ", STDERR_FILENO);
	ft_putstr_fd(EM_UNEXPECTED_TOKEN, STDERR_FILENO);
	ft_putstr_fd(" \'", STDERR_FILENO);
	if (!token_next_valid(dt))
		ft_putstr_fd("newline", STDERR_FILENO);
	else
		ft_putstr_fd(dt->str, STDERR_FILENO);
	ft_putendl_fd("\'", STDERR_FILENO);
}

static int	check_head(t_meta *m, t_token *ct)
{
	if (ct->type == T_PIP || ((ct->type & DELIM) && !token_next_valid(ct)))
	{
		if (!ct->prev)
		{
			m->exit_status = 2;
			print_syntax_error(ct);
			return (1);
		}
	}
	return (0);
}

int	check_syntax_error(t_meta *m)
{
	t_token	*ct;
	t_token	*dt;

	ct = m->token_start;
	if (check_head(m, ct))
	{
		m->exit_status = 2;
		return (1);
	}
	while (ct)
	{
		dt = token_next_delim(ct);
		if (dt)
		{
			if (!dt->next || (dt->next->type & DELIM))
			{
				m->exit_status = 2;
				print_syntax_error(dt);
				return (1);
			}
		}
		ct = dt;
	}
	return (0);
}
