/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_sub_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 18:42:46 by tjung             #+#    #+#             */
/*   Updated: 2022/03/12 12:03:05 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

// norm 분리 - builtin_cd 연장
int	sub_builtin_cd(t_meta *m, char *path)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = env_get(m, "PWD");
	if (chdir(path) == -1)
		perror_exit("chdir(path) failed @builtin_cd/sub_builtin_cd");
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		free(oldpwd);
		perror_exit("getcwd failed @builtin_cd/sub_builtin_cd");
	}
	if (env_set(m, "OLDPWD", oldpwd) || env_set(m, "PWD", pwd))
	{
		custom_char_free(oldpwd, pwd);
		perror_exit("env_set() failed @builtin_cd/sub_builtin_cd");
	}
	m->exit_status = 0;
	custom_char_free(oldpwd, pwd);
	return (0);
}
