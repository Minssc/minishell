/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:46:38 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/03 12:21:30 by tjung            ###   ########.fr       */
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
	free(m);
}
