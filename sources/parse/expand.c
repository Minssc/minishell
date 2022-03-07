/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:12:15 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/07 14:34:00 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	find_key(char **pos)
{
	if (**pos == '?')
	{
		(*pos)++;
		return ;
	}
	while (**pos && !ms_isspace(**pos) && **pos != '$' &&
			**pos !='\'' && **pos != '\"' && **pos != '\\')
		(*pos)++;
}

void	insert_env(t_meta *m, char **ostr, char **epos) 
{
	char	*nstr;
	char	*key;
	char	*env_val;
	char	*orig;
	
	nstr = 0;
	orig = *ostr;
	if (*ostr != *epos)
		nstr = ft_substr(*ostr, 0 , (*epos) - (*ostr));
	*ostr = (*epos)++;
	find_key(epos);
	key = ms_substr(*ostr, 1, (*epos) - (*ostr) - 1);
	if (key[0] == '?')
		env_val = ft_itoa(m->exit_status);
	else
		env_val = env_get(m, key);
	ms_stitch(&nstr, env_val);
	ms_stitch(&nstr, *epos);
	free(orig);
	free(env_val);
	free(key);
	*ostr = nstr;
}

void	expand(t_meta *m)
{
	t_token	*ct;
	char	*exp;
	char	*cur;

	ct = m->token_start;
	while (ct)
	{
		exp = find_e(ct->str);
		while (exp)
		{
			insert_env(m, &ct->str, &exp);
			exp = find_e(ct->str);
		}
		ct = ct->next;
	}
}