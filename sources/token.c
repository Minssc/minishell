/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 20:08:19 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/03 22:20:11 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	token_ident(t_meta *m)
{
	t_token	*ct;

	ct = m->token_start;
	while (ct)
	{
		if (ft_strncmp(ct->str, "|", 1) == 0)
			ct->type = T_PIP;
		else if (ft_strncmp(ct->str, "<<", 2) == 0)
			ct->type = T_APL;
		else if (ft_strncmp(ct->str, ">>", 2) == 0)
			ct->type = T_APR;
		else if (ft_strncmp(ct->str, "<", 1) == 0)
			ct->type = T_RDL;
		else if (ft_strncmp(ct->str, ">", 1) == 0)
			ct->type = T_RDR;
		else if (!ct->prev || (ct->prev->type & 0b11111100))
			ct->type = T_CMD;
		else
			ct->type = T_ARG;
		ct = ct->next;
	}
}