/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 18:51:40 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/08 20:15:00 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	bin_find_paths(char **paths, char *bin)
// paths들을 순회하며 bin이 발견될 시 path 반환. 못찾으면 0 반환

static char	*bin_find_paths(char **paths, char *bin)
{
	DIR				*dir;
	char			**cur;
	struct dirent	*item;
	// const size_t	blen = ft_strlen(bin);

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
	const size_t	plen = ft_strlen(*path);
	const size_t	flen = ft_strlen(file);
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

static int	check_error(t_meta *m, char *bin)
{
	DIR *dir;
	int	fd;
	int	ret;
	int	is_root;

	ret = 0;
	is_root = (ft_strchr(bin, '/') == 0);
	fd = open(bin, O_WRONLY);
	dir = opendir(bin);
	if (is_root)
		ms_puterr(bin, EM_CMD_NOT_FOUND);
	else if (fd == -1 && !dir)
		ms_puterr(bin, EM_NO_SUCH_FILE_DIR);
	else if (fd == -1 && dir)
		ms_puterr(bin, EM_IS_DIR);
	else if (fd != -1 && dir)
		ms_puterr(bin, EM_PERM_DENIED);
	if (is_root && fd == -1 && !dir)
		ret = UCMD;
	else
		ret = ISDIR;
	fd_close(fd);
	if (dir)
		closedir(dir);
	return (ret);
}
// find binary file and run it.  

int	bin_run(t_meta *m, char *bin)
{
	char	**env;
	int		ret;

	ret = 0;
	m->pid = fork();
	if (m->pid == 0)
	{
		env = env_build(m);
		if (ft_strchr(bin, '/') && execve(bin, m->argv, env) == -1); 
			ret = check_error(m, bin);
		ms_free_dca(&env);
		mexit(ret);
	}
	else
		waitpid(m->pid, &ret, 0);
	ret = WEXITSTATUS(ret);
	return (ret);
}
