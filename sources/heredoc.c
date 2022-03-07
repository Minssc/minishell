/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 01:13:38 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/07 14:32:44 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
}

static void	readdoc(t_meta *m, t_token *tok)
{
	int		fd;
	char	*inp;
	char	*exp;

	fd = open(HEDOC, O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
	while (1)
	{
		inp = readline("> ");
		if (!inp || !ft_strcmp(tok->str, inp))
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
	ms_free((void **)&inp);
	fd_close(fd);
}

void	heredoc(t_meta *m, t_token *tok)
{
	int		last_hdoc;

	last_hdoc = 1;
	readdoc(m, tok);
	while (tok)
	{
		if (tok->type == T_APL)
			last_hdoc = 0;
		if (tok->type == T_PIP)
			break ;
		tok = tok->next;
	}
	if (!last_hdoc)
		return ;
	fd_close(m->fd_in);
	m->fd_in = open(HEDOC, O_RDONLY, S_IRWXU);
	dup2(m->fd_in, STDIN_FILENO);
}