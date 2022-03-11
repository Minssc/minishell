/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:57:59 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/11 23:13:54 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_set_shlvl(t_meta *m)
{
	char	*shlvl_c;
	int		shlvl_n;

	shlvl_c = env_get(m, "SHLVL");
	shlvl_n = ft_atoi(shlvl_c);
	free(shlvl_c);
	shlvl_n += 1;
	shlvl_c = ft_itoa(shlvl_n);
	if (env_set(m, "SHLVL", shlvl_c))
		perror_exit("env_set() failed @env_init/env_set_shlvl");
	free(shlvl_c);
}

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
	env_set_shlvl(m);
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
