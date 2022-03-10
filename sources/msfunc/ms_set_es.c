/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_set_es.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:18:16 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/10 22:58:20 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// update exit status only when current exit status is 0
// do not update if supplied exit_status is 0.
// returns 1 when failed, 0 when success

int	ms_set_es(t_meta *m, int exit_status)
{
	if (m->exit_status && !exit_status)
		return (1);
	m->exit_status = exit_status;
	return (0);
}
