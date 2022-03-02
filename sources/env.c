/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 22:57:59 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/03 01:24:16 by minsunki         ###   ########seoul.kr  */
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

// TODO getenv setenv 
// maybe create K:V struct for env instead of raw list. 
// for now, use list of K=V string.

// t_list	*env_find(t_meta *m, char *key)
// m->list_env에서 key값을 가진 환경 변수 t_list*를 반환.
// 못찾으면 0 반환

t_list	*env_find(t_meta *m, char *key)
{
	size_t	klen;
	t_list	*cur;

	if (!key)
		return (0);
	cur = m->list_env;
	while (cur)
	{
		if (strncmp((char *)cur->content, key, klen) == 0)
			return (cur);
		cur = cur->next;
	}
	return (0);
}

// char	*env_get(char *key)
// key에 해당하는 환경변수 value 를 반환.
// 못찾으면 0 반환 
// 반환 값 알아서 free 할것!!!

char	*env_get(t_meta *m, char *key)
{
	char	*ret;
	size_t	klen;
	t_list	*entry;

	if (!key)
		return (0);
	klen = ft_strlen(key);
	entry = env_find(m, key);
	if (!entry)
		return (0);
	ret = ft_strdup(((char *)entry->content + klen + 1));
	if (!ret)
		perror_exit("ft_strdup failed @env_get");
	return (ret);
}

static char	*merge_kv(char *key, char *value)
{
	char	*ret;
	size_t	klen;
	size_t	vlen;
	int		i;

	klen = ft_strlen(key);
	vlen = ft_strlen(value);
	ret = (char *)malloc(sizeof(char) * (klen + vlen + 1 + 1));
	if (!ret)
		perror_exit("malloc failed @merge_kv");
	ret[klen + vlen + 1] = '\0';
	i = -1;
	while (++i < klen)
		ret[i] = key[i];
	ret[i] = '=';
	i = -1;
	while (++i < vlen)
		ret[klen + 1 + i] = value[i];
	return (ret);
}

// char	*env_set(char *key, char *value)
// key=value entry를 m->list_env에 추가.
// 이미 있으면 value 덮어씌움 TODO 이게 맞는지 확인하기
// 성공 시 0 반환, 실패 시 1 반환 
// key, value를 해제해 주지 않음. 알아서 해제할것

int		env_set(t_meta *m, char *key, char *value)
{
	size_t	klen;
	// t_list	*cur;
	t_list	*entry;
	t_list	*nl;

	if (!key || !value)
		return (1);
	entry = env_find(m, key);
	if (entry)
	{
		free(entry->content);
		entry->content = merge_kv(key, value);
		if (!entry->content)
			perror_exit("ft_lstnew failed @env_set");
		return (0);
	}
	nl = ft_lstnew(merge_kv(key, value));
	if (!nl)
		perror_exit("ft_lstnew failed @env_set");
	ft_lstadd_back(&m->list_env, nl);
	return (0);
}