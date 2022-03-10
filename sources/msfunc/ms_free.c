/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 15:01:19 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/10 19:21:31 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	ms_free(void **ptr)
// free the supplied ptr and zero it out as well.

void	ms_free(void **ptr)
{
	if (!ptr || !(*ptr))
		return ;
	free(*ptr);
	*ptr = 0;
}

// void	ms_free_dca(char ***dca)
// free and zero out a double character array.
// has to be null filled and null terminated.

void	ms_free_dca(char ***dca)
{
	char	**tdca;

	if (!dca || !(*dca))
		return ;
	tdca = *dca;
	while (*tdca)
	{
		free(*tdca);
		*tdca = 0;
		tdca++;
	}
	free(*dca);
	*dca = 0;
}
