/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 19:20:00 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/06 01:22:19 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// static char	*find_q(char *str)
// {
// 	while (*str)
// 	{
// 		if (*str == '\'' || *str == '\"')
// 			return (str);
// 		str++;
// 	}
// 	return (0);
// }

// static int	count_quotes(char *str)
// {
// 	int	cnt;
	
// 	cnt = 0;
// 	while (*str)
// 	{
// 		if (*str == '\'' || *str == '\"')
// 			cnt++;
// 		str++;
// 	}
// 	return (cnt);
// }

// static void	remove_quotes(char **ostr)
// {
// 	char	*nstr;
// 	char	*orig;
// 	int		nquotes;
// 	int		i;
// 	int		olen;

// 	i = 0;
// 	orig = *ostr;
// 	nquotes = count_quotes(*ostr);
// 	olen = ft_strlen(*ostr);
// 	nstr = (char *)malloc(sizeof(char) * (olen - nquotes + 1));
// 	nstr[olen - nquotes] = '\0';
// 	while (**ostr)
// 	{
// 		if (**ostr != '\'' && **ostr != '\"')
// 			nstr[i++] = **ostr;
// 		(*ostr)++;
// 	}
// 	free(orig);
// 	*ostr = nstr;
// }

// static int	get_nlen(char *str)
// {
// 	int		ret;
// 	char	lq;

// 	ret = 0;
// 	lq = 0;
// 	while (*str)
// 	{
// 		if (*str == '\\')
// 		{
// 			if (!lq && *(str + 1) == '$' || *(str + 1) == '\"' ||
// 					*(str + 1) == '\'')
// 				str++;
// 			else if (lq && lq == '\"')
// 			{

// 			}
// 		}
// 		else if (!lq && *str == '\"' || *str == '\'')
// 		{
// 			lq = *str;
// 		}
// 		else if (lq && (*str == '\"' || *str == '\''))
// 		{
// 			if (lq != *str)
// 				ret++;
// 			else
// 				lq = 0;
// 		}
// 		str++;
// 	}
// 	return (ret);
// }

// static void	remove_quotes_and_escape(char **ostr)
// {
// 	const size_t	olen = ft_strlen(*ostr);
// 	char			*nstr;
// 	char			*cstr;
// 	int				nlen;

// 	nlen = get_nlen(*ostr);
// }

// static char	*needs_cleanup(char *str)
// {
// 	while (*str)
// 	{
// 		if (*str == '\'' || *str == '\"')
// 			return (0);
// 		str++;
// 	}
// 	return (0);
// }

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