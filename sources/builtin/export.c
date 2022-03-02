/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:52:12 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/03 00:00:37 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*except_quotes(char *tmp)
// {
// 	char	*value;
// 	int		qflag;
// 	int		i;

// 	qflag = 0;
// 	i = -1;
// 	while (tmp[++i])
// 	{
// 		if (tmp[i] == '\"')
// 			i++;
// 	}
// }

// static char	*join_key_and_value(char *chunk, char *tmp, char *equal)
// {
// 	char	*join;
// 	char	*keye;
// 	char	*value;

// 	keye = ft_substr(chunk, 0, (equal + 1) - chunk);
// 	value = except_quotes(tmp);
// 	join = ft_strjoin(keye, value);
// 	free(keye);
// 	free(value);
// 	return (join);
// }

// static char	*valid_chunk(char *chunk)
// {
// 	char	*var;
// 	char	*tmp;
// 	char	*equal;
// 	int		len;

// 	equal = ft_strchr(chunk, '=');
// 	if (!equal)
// 		return (NULL);
// 	len = ft_strlen(equal) - 1;
// 	tmp = ft_substr(chunk, (equal + 1) - chunk, len);
// 	var = join_key_and_value(chunk, tmp, equal);
// 	free(tmp);
// 	return (var);
// }

// int	mini_export(t_env *root, char *chunk)
// {
// 	t_env	*last;
// 	char	*env_variable;

// 	env_variable = valid_chunk(chunk);
// 	if (env_variable)
// 	{
// 		last = ft_lstlast_env(root);
// 		ft_lstadd_back_env(&last, ft_lstnew_env());
// 		last = last->next;
// 		last->contents = env_variable;
// 	}
// 	g_exit_status = 0;
// 	return (0);
// }
