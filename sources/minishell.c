/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 14:52:53 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/02 15:01:00 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ms_loop(t_meta *m)
{
	char	*line;

	line = readline("minishell$ ");
	if (line)
	{
		printf("read: %s\n",line);
	}
	return (1);
}