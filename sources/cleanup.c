/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 19:20:00 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/06 01:28:06 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO reduce function count

static void	escape(char **str)
{
	char	nc;

	nc = *(*str + 1);
	(*str)++;
}

static int	quotes(char **str)
{
	int		ret;
	char	quote;

	ret = 0;
	quote = *(*str)++;
	while (**str)
	{
		if (quote == '\"' && **str == '\\')
		{
			if (*(++(*str)) == '\"')
			{
				ret++;
				(*str)++;
			}
			continue ;
		}
		if (quote == **str)
			break ;
		else
		{
			(*str)++;
			ret++;
		}
	}
	return (ret);
}

static int	get_nlen(char *str)
{
	int		ret;
	char	quote;

	ret = 0;
	while (*str)
	{
		if (*str == '\\')
		{
			str++;
			if (*str == '\"' || *str == '\'' || *str == '\\')
			{
				str++;
				ret++;
			}
			continue ;
		}
		if (*str == '\'' || *str == '\"')
			ret += quotes(&str);
		else 
			ret++;
		str++;
	}
	return (ret);
}

static void	nstr_quotes(char **str, char **ret, int *i)
{
	char	quote;

	quote = *(*str)++;
	while (**str)
	{
		if (quote == '\"' && **str == '\\')
		{
			if (*(++(*str)) == '\"')
			{
				(*ret)[(*i)++] = **str;
				(*str)++;
			}
			continue ;
		}
		if (quote == **str)
			break ;
		else
		{
			(*ret)[(*i)++] = **str;
			(*str)++;
		}
	}
}

static char	*make_nstr(char *str, int nlen)
{
	char	*ret;
	int		i;

	i = 0;
	ret = (char *)ft_calloc(sizeof(char), nlen + 1);
	if (!ret)
		perror_exit("ft_calloc failed @make_nstr");
	while (*str)
	{
		if (*str == '\\')
		{
			if (*(++str) == '\"' || *str == '\'' || *str == '\\')
			{
				ret[i++] = *str;
				str++;
			}
			continue ;
		}
		if (*str == '\'' || *str == '\"')
			nstr_quotes(&str, &ret, &i);
		else
			ret[i++] = *str;
		str++;
	}
	return (ret);
}

void	cleanup(t_meta *m)
{
	t_token	*ct;
	char	*qp;
	char	*tmp;
	int		nlen;

	ct = m->token_start;
	while (ct)
	{
		// remove_quotes_and_escape(&ct->str);
		nlen = get_nlen(ct->str);
		// printf("%s#len: %d, nlen: %d\n",ct->str,ft_strlen(ct->str),nlen);
		if (nlen != ft_strlen(ct->str))
		{
			tmp = ct->str;
			ct->str = make_nstr(ct->str, nlen);
			// printf("nlen:%s#\n",ct->str);
			free(tmp);
		}
		ct = ct->next;
	}
}