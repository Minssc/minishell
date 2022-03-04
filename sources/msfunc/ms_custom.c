/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_custom.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 19:53:05 by tjung             #+#    #+#             */
/*   Updated: 2022/03/04 20:32:11 by tjung            ###   ########.fr       */
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
