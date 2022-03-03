/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:52:12 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/03 18:29:37 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// opt 1 -> key, opt 2 -> value
static char	*get_data(char *entry, char *equal, char opt)
{
	char	*str;
	int		len;

	if (opt == 'k')
	{
		len = equal - entry;
		str = ft_substr(entry, 0, len);
	}
	else if (opt == 'v')
	{
		len = ft_strlen(equal) - 1;
		str = ft_substr(entry, (equal + 1) - entry, len);
	}
	return (str);
}

// norm 분리 - builtin_export 연장
static int	exec_export(t_meta *m, char *entry, char *equal)
{
	char	*key;
	char	*value;
	int		ret;

	key = get_data(entry, equal, 'k');
	value = get_data(entry, equal, 'v');
	ret = env_set(m, key, value);
	free(key);
	free(value);
	return (ret);
}

//entries[0] = export 명령어
int	builtin_export(char **entries)
{
	t_meta	*m;
	char	*entry;
	char	*equal;
	int		i;

	m = meta_get();
	i = 0;
	while (entries[++i])
	{
		equal = ft_strchr(entries[i], '=');
		if (!equal)
			continue ;
		if (exec_export(m, entries[i], equal))
			perror_exit("env_set failed @builtin_export");
	}
	m->exit_status = 0;
	return (0);
}
