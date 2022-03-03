/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:52:12 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/02 20:39:44 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_value_len(char *tmp)
{
	int	len;
	int	qflag;
	int	i;

	qflag = 0;
	i = -1;
	while (tmp[++i])
	{
		if (!qflag && tmp[i] == '\"')
			i++;
		else if (!qflag && tmp[i] == '\'')
			i++;
	}
	return (len);
}

static char	*except_quotes(char *tmp)
{
	char	*value;
	int		v_len;
	int		qflag;
	int		i;
	int		j;

	qflag = 0;
	v_len = get_value_len(tmp);
	value = (char *)malloc(sizeof(char) * v_len + 1);
	if (!value)
		return (NULL);
	value[v_len] = '\0';
	i = 0;
	j = 0;
	while (value[i])
	{
		if (tmp[j] == '\"')
			j++;
		value[i++] = tmp[j++];
	}
}

static char	*join_key_and_value(char *chunk, char *tmp, char *equal)
{
	char	*join;
	char	*keye;
	char	*value;

	keye = ft_substr(chunk, 0, (equal + 1) - chunk);
	value = except_quotes(tmp);
	join = ft_strjoin(keye, value);
	free(keye);
	free(value);
	return (join);
}

static char	*valid_chunk(char *chunk)
{
	char	*var;
	char	*tmp;
	char	*equal;
	int		len;

	equal = ft_strchr(chunk, '=');
	if (!equal)
		return (NULL);
	len = ft_strlen(equal) - 1;
	tmp = ft_substr(chunk, (equal + 1) - chunk, len);
	var = join_key_and_value(chunk, tmp, equal);
	free(tmp);
	return (var);
}

int	mini_export(t_env *root, char *chunk)
{
	t_env	*last;
	char	*env_variable;

	env_variable = valid_chunk(chunk);
	if (env_variable)
	{
		last = ft_lstlast_env(root);
		ft_lstadd_back_env(&last, ft_lstnew_env());
		last = last->next;
		last->contents = env_variable;
	}
	g_exit_status = 0;
	return (0);
}
