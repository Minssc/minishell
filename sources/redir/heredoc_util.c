/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:22:52 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/11 13:39:36 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc_getname(int num)
{
	char	*nascii;
	char	*tmp;
	char	*ret;

	ret = ft_strdup("/tmp/minishell_heredoc_");
	if (!ret)
		perror_exit("ft_strdup failed @heredoc_getname");
	nascii = ft_itoa(num);
	if (!nascii)
	{
		free(ret);
		perror_exit("ft_itoa failed @heredoc_getname");
	}
	tmp = ret;
	ret = ft_strjoin(ret, nascii);
	if (!ret)
	{
		free(tmp);
		free(nascii);
		perror_exit("ft_strjoin failed @heredoc_getname");
	}
	free(tmp);
	free(nascii);
	return (ret);
}

static void	escape_and_write(char *str, int fd)
{
	while (*str)
	{
		if (*str == '\\')
			str++;
		ft_putchar_fd(*str, fd);
		str++;
	}
	ft_putchar_fd('\n', fd);
}

static char	*find_exp(char *str)
{
	while (*str)
	{
		if (*str == '\\' && *(str + 1) == '$')
			str += 2;
		if (*str == '$')
			return (str);
		str++;
	}
	return (0);
}

static void	eolmsg(t_meta *m)
{
	ft_putstr_fd("-minishell: here-document delimited by", STDERR_FILENO);
	ft_putstr_fd(" end-of-file (wanted '", STDERR_FILENO);
	ft_putstr_fd(m->hd_str, STDERR_FILENO);
	ft_putendl_fd("')", STDERR_FILENO);
}

void	heredoc_read(t_meta *m)
{
	char	*exp;

	while (1)
	{
		m->line = readline("> ");
		if (!m->line)
		{
			eolmsg(m);
			ms_free((void **)&m->line);
			break ;
		}
		if (ft_strcmp(m->hd_str, m->line) == 0)
		{
			ms_free((void **)&m->line);
			break ;
		}
		exp = find_exp(m->line);
		while (exp)
		{
			insert_env(m, &m->line, &exp);
			exp = find_exp(m->line);
		}
		escape_and_write(m->line, m->hd_fd);
		ms_free((void **)&m->line);
	}
}
