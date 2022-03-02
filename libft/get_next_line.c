/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 23:20:08 by minsunki          #+#    #+#             */
/*   Updated: 2021/08/03 15:23:37 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**get_buffer(void)
{
	static char	*buf;

	return (&buf);
}

static int	get_line(char **dat, char **ret)
{
	char		*nlp;
	char		*tmp;

	nlp = ft_strchr(*dat, '\n');
	if (*dat && nlp)
	{
		*nlp = '\0';
		tmp = *dat;
		*ret = ft_strdup(*dat);
		*dat = ft_strdup(nlp + 1);
		free(tmp);
		return (1);
	}
	return (0);
}

static int	gnl_eof(char **dat, char **ret)
{
	if (*dat && get_line(dat, ret))
		return (1);
	else if (*dat)
	{
		*ret = *dat;
		*dat = 0;
		return (0);
	}
	*ret = ft_strdup("");
	return (0);
}

int	get_next_line(int fd, char **line)
{
	char		**dat;
	char		*tmp;
	char		buf[BUFFER_SIZE + 1];
	ssize_t		rbytes;

	dat = get_buffer();
	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	while (1)
	{
		rbytes = read(fd, buf, BUFFER_SIZE);
		if (rbytes <= 0)
			break ;
		buf[rbytes] = '\0';
		tmp = *dat;
		*dat = ft_strjoin(*dat, buf);
		if (tmp)
			free(tmp);
		if (get_line(dat, line))
			return (1);
	}
	if (rbytes < 0)
		return (-1);
	return (gnl_eof(dat, line));
}

void	get_next_line_clear(void)
{
	char		**buf;

	buf = get_buffer();
	if (!*buf)
		return ;
	free(*buf);
	*buf = 0;
}
