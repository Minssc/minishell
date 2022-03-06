/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:57:59 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/07 01:35:40 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_init(t_meta *m, char **envp)
{
	t_list	*nl;
	char	**cur;

	cur = envp;
	while (*cur)
	{
		nl = ft_lstnew(ft_strdup(*cur));
		if (!nl)
			perror_exit("ft_lstnew failed @env_init");
		if (!nl->content)
			perror_exit("ft_strdup failed @env_init");
		ft_lstadd_back(&m->list_env, nl);
		cur++;
	}
}

// char	**env_build(t_meta *m)
// convert env list to double char array.
// null terminated. 

char	**env_build(t_meta *m)
{
	int		i;
	int		size;
	t_list	*cur;
	char	**ret;

	size = 0;
	cur = m->list_env;
	while (cur)
	{
		size++;
		cur = cur->next;
	}
	ret = (char **)ft_calloc(sizeof(char *), size + 1);
	if (!ret)
		perror_exit("ft_calloc failed @env_build");
	cur = m->list_env;
	i = 0;
	while (cur)
	{
		ret[i++] = ft_strdup((char *)cur->content);
		cur = cur->next;
	}
	return (ret);
}

void	env_destroy(t_meta *m)
{
	if (!m->list_env)
		return ;
	ft_lstclear(&m->list_env, free);
	ms_free((void **)(&m->list_env));
}
