/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 01:17:07 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/10 18:55:30 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_list	*env_find(t_meta *m, char *key)
// m->list_env에서 key값을 가진 환경 변수 t_list*를 반환.
// 못찾으면 0 반환

t_list	*env_find(t_meta *m, char *key)
{
	size_t	klen;
	t_list	*cur;

	if (!key)
		return (0);
	klen = ft_strlen(key);
	cur = m->list_env;
	while (cur)
	{
		if (ft_strncmp((char *)cur->content, key, klen) == 0
			&& ((char *)(cur->content))[klen] == '=')
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
	int		klen;
	int		vlen;
	int		i;

	klen = (int)ft_strlen(key);
	vlen = (int)ft_strlen(value);
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

int	env_set(t_meta *m, char *key, char *value)
{
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
