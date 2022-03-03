/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unquote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 19:20:00 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/03 19:37:45 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static char	*find_q(char *str)
{
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			return (str);
		str++;
	}
	return (0);
}

static int	count_quotes(char *str)
{
	int	cnt;
	
	cnt = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
			cnt++;
		str++;
	}
	return (cnt);
}

static void	remove_quotes(char **ostr)
{
	char	*nstr;
	char	*orig;
	int		nquotes;
	int		i;
	int		olen;

	i = 0;
	orig = *ostr;
	nquotes = count_quotes(*ostr);
	olen = ft_strlen(*ostr);
	nstr = (char *)malloc(sizeof(char) * (olen - nquotes));
	nstr[olen - nquotes - 1] = '\0';
	while (**ostr)
	{
		if (**ostr != '\'' && **ostr != '\"')
			nstr[i++] = **ostr;
		(*ostr)++;
	}
	free(orig);
	*ostr = nstr;
}

void	unquote(t_meta *m)
{
	t_token	*ct;
	char	*qp;

	if (!m->token_start)
		return ;
	ct = m->token_start;
	while (ct)
	{
		qp = find_q(ct->str);
		if (qp)
			remove_quotes(&ct->str);
		ct = ct->next;
	}
}