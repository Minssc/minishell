/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 12:51:45 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/05 23:09:02 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 문자열의 끝 \0 공간까지 포함한 길이
static int	str_size(char **contents, int i)
{
	int	size;

	size = 0;
	while (contents[i])
	{
		size += ft_strlen(contents[i]);
		size += 1;
		i++;
	}
	return (size);
}

// opt_n 과 "-n" 을 비교 -> 같으면 1, 다르면 0
static int	check_opt_n(char *opt_n)
{
	if (!ft_strcmp(opt_n, "-n"))
		return (1);
	return (0);
}

// norm 분리 - builtin_echo 연장
static void	sub_builtin_echo(char **contents, char *sum, int i)
{
	int	j;
	int	k;

	j = 0;
	while (contents[++i])
	{
		k = 0;
		while (contents[i][k])
			sum[j++] = contents[i][k++];
		if (contents[i + 1] != NULL)
			sum[j++] = ' ';
	}
	sum[j] = '\0';
}

int	builtin_echo(char **contents)
{
	t_meta	*m;
	char	*sum;
	int		is_n;
	int		size;
	int		i;

	m = meta_get();
	if (custom_double_char_len(contents) == 1)
		return (custom_putendl("", 0));
	is_n = check_opt_n(contents[1]);
	i = 0;
	if (is_n)
		++i;
	size = str_size(contents, i + 1);
	sum = (char *)malloc(sizeof(char) * size);
	if (!sum)
		perror_exit("malloc error @builtin_echo");
	sub_builtin_echo(contents, sum, i);
	if (is_n)
		ft_putstr_fd(sum, STDOUT_FILENO);
	else
		ft_putendl_fd(sum, STDOUT_FILENO);
	free(sum);
	m->exit_status = 0;
	return (0);
}
