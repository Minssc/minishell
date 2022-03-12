/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:52:12 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/12 12:03:05 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

// norm 분리 - sub_builtin_export 연장
static int	sub_sub_export(t_meta *m, char *key, char *value)
{
	char	*tmp;
	int		ret;

	tmp = get_value_plus(key, value);
	if (!tmp)
		ret = env_set(m, key, value);
	else
		ret = env_set(m, key, tmp);
	if (tmp)
		free(tmp);
	return (ret);
}

// norm 분리 - builtin_export 연장
static int	sub_builtin_export(t_meta *m, char *entry, char *equal)
{
	char	*key;
	char	*value;
	int		ret;

	ret = 0;
	key = get_key(entry, equal, &ret);
	if (!ret)
	{
		value = get_data(entry, equal, 'v', 0);
		if (entry[equal - entry - 1] == '+')
			ret = sub_sub_export(m, key, value);
		else
			ret = env_set(m, key, value);
		if (ret)
			perror_exit("env_set failed @builtin_export");
		custom_char_free(key, value);
	}
	else
		free(key);
	return (ret);
}

//entries[0] = export 명령어
int	builtin_export(char **entries)
{
	t_meta	*m;
	char	*equal;
	int		i;

	m = meta_get();
	i = 0;
	while (entries[++i])
	{
		equal = ft_strchr(entries[i], '=');
		if (!equal)
			continue ;
		if (sub_builtin_export(m, entries[i], equal))
		{
			m->exit_status = 1;
			return (1);
		}
	}
	m->exit_status = 0;
	return (0);
}
