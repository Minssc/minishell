/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_custom.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 19:53:05 by tjung             #+#    #+#             */
/*   Updated: 2022/03/04 21:54:32 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	custom_char_free(char *one, char *two)
{
	if (one)
		free(one);
	if (two)
		free(two);
}

int	custom_double_char_len(char **ptr)
{
	int	len;

	len = 0;
	while (ptr[len])
		++len;
	return (len);
}

// builtin/cd.c 를 위한 맞춤 norm 회피 함수...
int	custom_perr_and_set_exnum(char *str, int exnum, char *heap, int ret)
{
	t_meta	*m;

	m = meta_get();
	ft_putendl_fd(str, STDERR_FILENO);
	m->exit_status = exnum;
	if (heap)
		free(heap);
	return (ret);
}
