/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 18:51:40 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/09 17:01:07 by minsunki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	process_stat(int stat)
{
	int	ret;

	ret = 0;
	if (WEXITSTATUS(stat))
		ret = WEXITSTATUS(stat);
	else if (WTERMSIG(stat))
	{
		ret = WTERMSIG(stat);
		ft_putendl_fd("Quit", STDERR_FILENO);
		ret += 128;
	}
	return (ret);
}

int	bin_run(t_meta *m, char *bin)
{
	char	**env;
	int		ret;

	ret = 0;
	m->waiting = 1;
	m->pid = fork();
	if (m->pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		env = env_build(m);
		if (ft_strchr(bin, '/') == 0 || execve(bin, m->argv, env) == -1)
			ret = check_error(m, bin);
		ms_free_dca(&env);
		mexit(ret);
	}
	else
		waitpid(m->pid, &ret, 0);
	m->waiting = 0;
	ret = process_stat(ret);
	return (ret);
}
