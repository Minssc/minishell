/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 18:51:40 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/07 02:01:34 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	bin_find_paths(char **paths, char *bin)
// paths들을 순회하며 bin이 발견될 시 path 반환. 못찾으면 0 반환

static char	*bin_find_paths(char **paths, char *bin)
{
	DIR				*dir;
	struct dirent	*item;
	// const size_t	blen = ft_strlen(bin);

	while (*paths)
	{
		dir = opendir(*paths);
		if (dir)
		{
			item = readdir(dir);
			while (item)
			{
				if (ft_strcmp(item->d_name, bin) == 0)
				{
					closedir(dir);
					return (*paths);
				}
				item = readdir(dir);
			}
			closedir(dir);
		}
		paths++;
	}
	return (0);
}

// static void	path_stitch(char **paths, char *file)
// stitch path and file to the supplied *path 
// takes care of both / terminated path and non terminated path.

static void	path_stitch(char **path, char *file)
{
	char			*tmp;
	const size_t	plen = ft_strlen(*path);
	const size_t	flen = ft_strlen(file);
	int				i;

	tmp = *path;
	if ((*path)[plen - 1] == '/')
	{
		*path = ft_strjoin(*path, file);
		free(tmp);
	}
	else
	{
		*path = (char *)ft_calloc(sizeof(char), plen + flen + 1 + 1);
		if (!(*path))
			perror_exit("ft_calloc failed @path_stitch");
		i = -1;
		while (++i < plen)
			(*path)[i] = tmp[i];
		(*path)[i] = '/';
		i = -1;
		while (++i < flen + 1)
			(*path)[plen + 1 + i] = file[i];
	}
}

char	*bin_find(t_meta *m, char *bin)
{
	char	*tmp;
	char	*path;
	char	**paths;
	
	path = env_get(m, "PATH");
	if (!path)
		return (0); 
	paths = ft_split(path, ':');
	if (!paths)
		perror_exit("ft_split failed @find_bin");
	free(path);
	path = bin_find_paths(paths, bin);
	if (!path)
		return (0);
	path_stitch(&path, bin);
	ms_free_dca(&paths);
	return (path);
}

// find binary file and run it.  

int	bin_run(t_meta *m, char *bin)
{
	char	**env;
	int		ret;

	m->pid = fork();
	if (m->pid == 0)
	{
		env = env_build(m);
		if (execve(bin, m->argv, env) == -1); // TODO manage errno
			printf("\nerrno: %d\n", errno);
		ms_free_dca(&env);
		mexit(ret);
	}
	else
		waitpid(m->pid, &ret, 0);
	return (ret);
}
