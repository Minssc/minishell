/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 01:03:06 by minsunki          #+#    #+#             */
/*   Updated: 2021/08/03 15:23:26 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**split_abort(char **darr)
{
	char	*arr;

	if (!darr)
		return (0);
	arr = *darr;
	while (arr)
	{
		free(arr);
		arr = 0;
		arr++;
	}
	free(darr);
	darr = 0;
	return (0);
}

static int	count_words(char const *cur, char c)
{
	int		ret;
	int		word;

	ret = 0;
	word = 0;
	while (*cur)
	{
		if (word && *cur == c)
		{
			ret++;
			word = 0;
		}
		else if (!word && *cur != c)
			word = 1;
		cur++;
	}
	if (word)
		ret++;
	return (ret);
}

char	*get_word(char const **s, char c)
{
	char	*ret;
	char	*cur;

	while (**s && **s == c)
		(*s)++;
	cur = ft_strchr(*s, c);
	if (!cur)
		ret = ft_strdup(*s);
	else
		ret = ft_substr(*s, 0, (size_t)(cur - *s));
	*s = cur;
	return (ret);
}

char	**ft_split(char const *s, char c)
{
	const int	nword = count_words(s, c);
	char		**ret;
	int			i;

	if (!s)
		return (0);
	ret = (char **)ft_calloc(nword + 1, sizeof(char *));
	if (!ret)
		return (split_abort(ret));
	ret[nword] = 0;
	i = -1;
	while (++i < nword)
	{
		ret[i] = get_word(&s, c);
		if (!ret[i])
			return (split_abort(ret));
	}
	return (ret);
}
