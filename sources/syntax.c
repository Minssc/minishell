/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 18:42:13 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/11 00:13:18 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_syntax_error(t_token *dt)
{
	ft_putstr_fd("-minishell: ", STDERR_FILENO);
	ft_putstr_fd(EM_UNEXPECTED_TOKEN, STDERR_FILENO);
	ft_putstr_fd(" \'", STDERR_FILENO);
	if (!dt->next)
		ft_putstr_fd("newline", STDERR_FILENO);
	else
		ft_putstr_fd(dt->str, STDERR_FILENO);
	ft_putendl_fd("\'", STDERR_FILENO);
}

int	check_syntax_error(t_meta *m)
{
	t_token	*ct;
	t_token	*dt;

	ct = m->token_start;
	while (ct)
	{
		dt = token_next_delim(ct);
		if (dt)
		{
			if (!dt->next || (dt->next->type != T_CMD))
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
