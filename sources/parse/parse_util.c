/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 00:15:17 by tjung             #+#    #+#             */
/*   Updated: 2022/03/11 20:47:29 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sub_parse(t_meta *m, char *line, char *cur)
{
	token_parse(m, line, cur);
	heredoc_init(m);
	expand(m);
	if (!m->token_start)
		return (1);
	if (check_syntax_error(m))
		return (1);
	sort_tokens(m);
	return (0);
}
