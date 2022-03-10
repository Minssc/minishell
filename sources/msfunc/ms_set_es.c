/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_set_es.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:18:16 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/11 02:02:48 by minsunki         ###   ########seoul.kr  */
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
