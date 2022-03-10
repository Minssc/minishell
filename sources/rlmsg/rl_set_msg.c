/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_set_msg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:46:08 by tjung             #+#    #+#             */
/*   Updated: 2022/03/10 22:50:35 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	insert_cdata(char *dest, char *src, int *idx, char end)
{
	int	j;

	j = 0;
	while (src[j])
		dest[(*idx)++] = src[j++];
	dest[(*idx)++] = end;
}

static char	*get_last_directoy(t_meta *m, char *pwd, int len_pwd, int idx)
{
	char	*home;

	home = env_get(m, "HOME");
	if (!ft_strcmp(pwd, home))
	{
		free(home);
		return (ft_strdup("~"));
	}
	free(home);
	if (!ft_strcmp(pwd, "/"))
		return (ft_strdup("/"));
	return (ft_substr(pwd, idx + 1, len_pwd - idx - 1));
}

void	rl_set_message(t_meta *m)
{
	char	*l_dir;
	char	*pwd;
	int		len_pwd;
	int		idx;

	pwd = env_get(m, "PWD");
	len_pwd = ft_strlen(pwd);
	idx = len_pwd - 1;
	while (idx)
	{
		if (pwd[idx] == '/')
			break ;
		--idx;
	}
	l_dir = get_last_directoy(m, pwd, len_pwd, idx);
	m->rl_msg = (char *)malloc(sizeof(char) * (ft_strlen(l_dir) + 16));
	idx = 0;
	insert_cdata(m->rl_msg, "[minishell:", &idx, ' ');
	insert_cdata(m->rl_msg, l_dir, &idx, ']');
	insert_cdata(m->rl_msg, "$", &idx, ' ');
	m->rl_msg[idx] = '\0';
	free(pwd);
	free(l_dir);
}
