/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sub.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 20:15:11 by tjung             #+#    #+#             */
/*   Updated: 2022/03/12 00:00:05 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// opt 1 -> key, opt 2 -> value
char	*get_data(char *entry, char *equal, char opt, int plus)
{
	char	*str;
	int		len;

	str = NULL;
	if (opt == 'k')
	{
		len = equal - entry;
		if (plus)
			str = ft_substr(entry, 0, len - 1);
		else
			str = ft_substr(entry, 0, len);
	}
	else if (opt == 'v')
	{
		len = ft_strlen(equal) - 1;
		str = ft_substr(entry, (equal + 1) - entry, len);
	}
	return (str);
}

int	check_invalid_key(char *key, int plus)
{
	int	size;
	int	idx;

	size = ft_strlen(key);
	idx = size;
	while (--idx >= 0)
	{
		if (key[idx] == '+' || key[idx] == '-')
		{
			if (plus)
				return (1);
			if (idx != size - 1)
				return (1);
		}
	}
	return (0);
}

int	error_check(char *entry, char *equal, char *key, int plus)
{
	if (key[0] == '\0' || entry[equal - entry - 1] == '-')
	{
		if (key[0] != '\0')
		{
			if (key[0] == '-' && key[1] == '\0')
				ms_puterr("-=", EM_INVALID_OPT);
			else if (key[0] == '-' && key[1] == '-')
				ms_puterr("--", EM_INVALID_OPT);
			else
				ms_puterr(entry, EM_INVALID_IDENT);
		}
		else
			ms_puterr(entry, EM_INVALID_IDENT);
	}
	else if (check_invalid_key(key, plus))
	{
		if (key[0] == '-' && key[1] == '-')
			ms_puterr("--", EM_INVALID_OPT);
		else
			ms_puterr(entry, EM_INVALID_IDENT);
	}
	else
		return (0);
	return (1);
}

char	*get_key(char *entry, char *equal, int *ret)
{
	char	*key;

	if (entry[equal - entry - 1] == '+')
	{
		key = get_data(entry, equal, 'k', 1);
		*ret = error_check(entry, equal, key, 1);
	}
	else
	{
		printf("free\n");
		key = get_data(entry, equal, 'k', 0);
		*ret = error_check(entry, equal, key, 0);
	}
	return (key);
}

char	*get_value_plus(char *key, char *value)
{
	t_meta	*m;
	char	*tmp1;
	char	*tmp2;

	m = meta_get();
	tmp2 = NULL;
	tmp1 = env_get(m, key);
	if (tmp1)
	{
		tmp2 = ft_strjoin(tmp1, value);
		free(tmp1);
		return (tmp2);
	}
	return (tmp2);
}
