/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asterisk_util_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 23:45:27 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/12 12:03:05 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"


static void	skip_quotes(char **str)
{
	char	quote;

	quote = **str;
	(*str)++;
	while (**str)
	{
		if (**str == quote)
			break ;
		else
			(*str)++;
	}
}

char	*find_ast(char *str)
{
	while (*str)
	{
		if (*str == '"' || *str == '\'')
			skip_quotes(&str);
		else if (*str == '\\' && *(str + 1) == '*')
			str++;
		else if (*str == '*')
			return (str);
		str++;
	}
	return (0);
}

static char	*asterisk_validate(char *dir, char *item, char *str)
{
	char	*ret;

	if (!asterisk_compare(dir, item, str))
		return (0);
	ret = ft_strjoin(dir, item);
	if (!ret)
		perror_exit("ft_strjoin failed @asterisk_validate");
	ms_stitch(&ret, ft_strchr(str, '/'));
	return (ret);
}

static void	search_dir(DIR *dir, t_list *list, char *cdir, char *str)
{
	struct dirent	*item;
	t_list			*nl;
	char			*nstr;

	item = readdir(dir);
	while (item)
	{
		if ((item->d_name)[0] != '.' || str[0] == '.')
		{
			nstr = asterisk_validate(cdir, item->d_name, str);
			if (nstr)
			{
				nl = ft_lstnew(nstr);
				if (!nl)
					perror_exit("ft_lstnew failed @asterisk_read_dir");
				ft_lstadd_back(&list, nl);
			}
		}
		item = readdir(dir);
	}
	closedir(dir);	
}

void	asterisk_read_dir(t_list *list, char *cdir, char *str)
{
	DIR				*dir;

	if (!cdir)
		dir = opendir(".");
	else
		dir = opendir(cdir);
	if (dir)
		search_dir(dir, list, cdir, str);
}
