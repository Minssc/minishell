/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 00:15:17 by tjung             #+#    #+#             */
/*   Updated: 2022/03/11 00:16:49 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sub_parse(t_meta *m, char *line, char *cur)
{
	token_parse(m, line, cur);
	sort_tokens(m);
	heredoc_init(m);
	expand(m);
}
