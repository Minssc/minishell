/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 16:22:52 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/09 16:35:34 by tjung            ###   ########.fr       */
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
			str+=2;
		if (*str == '$')
			return (str);
		str++;
	}
	return (0);
}

void	heredoc_read(t_meta *m, char *tstr, int fd)
{
	char	*inp;
	char	*exp;

	while (1)
	{
		inp = readline("> ");
		if (!inp || !ft_strcmp(tstr, inp))
			break ;
		exp = find_exp(inp);
		while (exp)
		{
			insert_env(m, &inp, &exp);
			exp = find_exp(inp);
		}
		escape_and_write(inp, fd);
		ms_free((void **)&inp);
	}
	if (inp)
		free(inp);
}