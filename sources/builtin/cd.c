/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:49:07 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/10 23:32:08 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 올바른 경로 return (0), 잘못된 경로 retrun (1)
static int	is_invalid_path(t_meta *m, char *path)
{
	char	*pwd;

	pwd = env_get(m, "PWD");
	if (chdir(path) == -1)
	{
		free(pwd);
		return (1);
	}
	if (chdir(pwd) == -1)
	{
		free(pwd);
		perror_exit("chdir(pwd) failed @builtin_cd/is_invalid_path");
	}
	free(pwd);
	return (0);
}

// "cd -" 명령에 대한 처리
static int	mv_oldpwd(t_meta *m)
{
	char	*oldpwd;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		perror_exit("getcwd failed @builtin_cd/mv_oldpwd");
	oldpwd = env_get(m, "OLDPWD");
	if (!oldpwd)
		return (custom_perr_and_set_exnum(EM_NO_ODLPWD, 1, pwd, 1));
	if (chdir(oldpwd) == -1)
	{
		custom_char_free(oldpwd, pwd);
		perror_exit("chdir(oldpwd) failed @builtin_cd/mv_oldpwd");
	}
	if (env_set(m, "OLDPWD", pwd) || env_set(m, "PWD", oldpwd))
	{
		custom_char_free(oldpwd, pwd);
		perror_exit("env_set() failed @builtin_cd/mv_oldpwd");
	}
	m->exit_status = 0;
	custom_char_free(oldpwd, pwd);
	return (0);
}

// "cd" 명령에 대한 처리
static int	mv_home(t_meta *m)
{
	char	*pwd;
	char	*home;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		perror_exit("getcwd failed @builtin_cd/mv_home");
	home = env_get(m, "HOME");
	if (chdir(home) == -1)
	{
		custom_char_free(pwd, home);
		perror_exit("chdir(home) failed @builtin_cd/mv_home");
	}
	if (env_set(m, "OLDPWD", pwd) || env_set(m, "PWD", home))
	{
		custom_char_free(pwd, home);
		perror_exit("env_set() failed @builtin_cd/mv_home");
	}
	m->exit_status = 0;
	custom_char_free(pwd, home);
	return (0);
}

// not a directory
static int	is_direc(t_meta *m, char *path)
{
	struct stat	buf;

	if (stat(path, &buf) == -1)
		ms_puterr(path, EM_NO_SUCH_FILE_DIR);
	else if ((buf.st_mode & S_IFMT) != S_IFDIR)
		ms_puterr(path, EM_NOT_DIR);
	else
		ms_puterr(path, EM_PERM_DENIED);
	m->exit_status = 1;
	return (1);
}

// 성공시 return (0), 실패시 retrun (1)
int	builtin_cd(char **mv_cmd)
{
	t_meta	*m;
	int		idx;

	m = meta_get();
	idx = custom_double_char_len(mv_cmd);
	if (idx == 1)
		return (mv_home(m));
	else if (idx == 2)
	{
		if (!ft_strncmp(mv_cmd[1], "~", 2))
			return (mv_home(m));
		if (!ft_strncmp(mv_cmd[1], "~/", 3))
			return (mv_home(m));
		if (!ft_strncmp(mv_cmd[1], "-", 2))
			return (mv_oldpwd(m));
		if (is_invalid_path(m, mv_cmd[1]))
			return (is_direc(m, mv_cmd[1]));
		return (sub_builtin_cd(m, mv_cmd[1]));
	}
	return (custom_perr_and_set_exnum(EM_TOO_MANY_ARGS, 1, NULL, 1));
}
