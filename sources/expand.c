/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:12:15 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/03 18:59:09 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_e(char *str)
{
	while (*str)
	{
		if (*str == '\'')
			ms_skip_quotes(&str, *str);
		else if (*str == '$' && *(str + 1) && !ms_isspace(*(str + 1)))
			return (str);
		str++;
	}
	return (0);
}

static void	stitch(char **s1, char *s2)
{
	char	*os1;
	
	os1 = *s1;
	*s1 = ft_strjoin(*s1, s2);
	free(os1);
}

static void	insert_env(t_meta *m, char **ostr, char **epos)
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
	while (**epos && !ms_isspace(**epos) && **epos != '$' &&
			**epos !='\'' && **epos != '\"')
		(*epos)++;
	key = ms_substr(*ostr, 1, (*epos) - (*ostr) - 1); // TODO branch when key == ?
	env_val = env_get(m, key);
	stitch(&nstr, env_val);
	stitch(&nstr, *epos);
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