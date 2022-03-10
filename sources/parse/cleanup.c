/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 19:20:00 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/10 22:58:45 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	quotes(char **str)
{
	int		ret;
	char	quote;

	ret = 0;
	quote = *(*str)++;
	while (**str)
	{
		if (quote == '\"' && **str == '\\' && *(*str + 1) == '\"')
		{
			ret++;
			(*str) += 2;
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
		if (quote == '\"' && **str == '\\' && *(*str + 1) == '\"')
		{
			(*ret)[(*i)++] = '\"';
			(*str) += 2;
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
	char	*tmp;
	size_t	nlen;

	ct = m->token_start;
	while (ct)
	{
		nlen = get_nlen(ct->str);
		if (nlen != ft_strlen(ct->str))
		{
			tmp = ct->str;
			ct->str = make_nstr(ct->str, nlen);
			free(tmp);
		}
		ct = ct->next;
	}
}
