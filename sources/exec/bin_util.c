/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 21:14:21 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/10 22:52:55 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	bin_find_paths(char **paths, char *bin)
// paths들을 순회하며 bin이 발견될 시 path 반환. 못찾으면 0 반환
// const size_t	blen = ft_strlen(bin);

static char	*bin_find_paths(char **paths, char *bin)
{
	DIR				*dir;
	char			**cur;
	struct dirent	*item;

	cur = paths;
	while (*cur)
	{
		dir = opendir(*cur);
		if (dir)
		{
			item = readdir(dir);
			while (item)
			{
				if (ft_strcmp(item->d_name, bin) == 0)
				{
					closedir(dir);
					return (*cur);
				}
				item = readdir(dir);
			}
			closedir(dir);
		}
		cur++;
	}
	return (0);
}

// static void	path_stitch(char **paths, char *file)
// stitch path and file to the supplied *path
// takes care of both / terminated path and non terminated path.

static int	path_stitch(char **path, char *file)
{
	char			*tmp;
	const int		plen = (int)ft_strlen(*path);
	const int		flen = (int)ft_strlen(file);
	int				i;

	tmp = *path;
	if ((*path)[plen - 1] == '/')
		*path = ft_strjoin(*path, file);
	else
	{
		*path = (char *)ft_calloc(sizeof(char), plen + flen + 1 + 1);
		if (!(*path))
			return (1);
		i = -1;
		while (++i < plen)
			(*path)[i] = tmp[i];
		(*path)[i] = '/';
		i = -1;
		while (++i < flen + 1)
			(*path)[plen + 1 + i] = file[i];
	}
	return (0);
}

char	*bin_find(t_meta *m, char *bin)
{
	char	*path;
	char	**paths;

	path = env_get(m, "PATH");
	if (!path)
		return (0);
	paths = ft_split(path, ':');
	free(path);
	if (!paths)
		perror_exit("ft_split failed @find_bin");
	path = bin_find_paths(paths, bin);
	if (!path)
	{
		ms_free_dca(&paths);
		return (0);
	}
	if (path_stitch(&path, bin))
	{
		ms_free_dca(&paths);
		perror_exit("ft_calloc failed @path_stitch");
	}
	ms_free_dca(&paths);
	return (path);
}
