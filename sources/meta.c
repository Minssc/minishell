/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:46:38 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/09 16:29:14 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_meta	*meta_get(void)
{
	static t_meta	*m;

	if (!m)
		m = (t_meta *)ft_calloc(sizeof(t_meta), 1);
	if (!m)
		perror_exit("ft_calloc failed @meta_get");
	return (m);
}

t_meta	*meta_init(void)
{
	t_meta	*m;

	m = meta_get();
	return (m);
}

void	meta_destroy(void)
{
	t_meta	*m;

	m = meta_get();
	token_destroy(m);
	env_destroy(m);
	argv_destroy(m);
	if (m->line)
		free(m->line);
	free(m);
}
