/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 18:51:40 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/04 20:20:40 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_dca(char **arr)
{
	char **orig;

	orig = arr;
	while (*arr)
		free(*(arr++));
	free(orig);
}

static int	file_check(char *file)
{

}

static void	path_stitch(char **paths, char *file)
{
	char			*tmp;
	size_t			plen;
	const size_t	flen = ft_strlen(file);
	int				i;

	while (*paths)
	{
		tmp = *paths;
		plen = ft_strlen(*paths);
		if ((*paths)[plen - 1] == '/')
			*paths = ft_strjoin(*paths, file);
		else
		{
			*paths = (char *)ft_calloc(sizeof(char), plen + flen + 1 + 1);
			if (!(*paths))
				perror_exit("ft_calloc failed @path_stitch");
			i = -1;
			while (++i < plen)
				(*paths)[i] = tmp[i];
			(*paths)[i] = '/';
			i = -1;
			while (++i < flen + 1)
				(*paths)[plen + 1 + i] = file[i];
		}
		free(tmp);
		paths++;
	}
}

static int	find_bin(t_meta *m, char *file)
{
	char	*tmp;
	char	*path;
	char	**paths;
	
	path = env_get(m, "PATH");
	if (!path)
		return (1); // TODO manage exit codes.
	paths = ft_split(path, ':');
	if (!paths)
		perror_exit("ft_split failed @find_bin");
	path_stitch(paths, file);
	free_dca(paths);
}

// find binary file and run it.  

void	execute_bin(t_meta *m)
{
	find_bin(m, m->argv[0]);
}