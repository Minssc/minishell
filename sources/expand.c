/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 15:12:15 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/03 18:57:44 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	find_and_sub(t_meta *m, t_list *li)
// {
// 	char	*cur;
// 	char	*tmp;
// 	char	*tmp2;
// 	char	*tmp3;
// 	int		i;

// 	cur = (char *)li->content;
// 	while (*cur)
// 	{
// 		i = 0;
// 		if (*cur == '\'')
// 		{
// 			cur++;
// 			while (*cur && *cur != '\'')
// 				cur++;
// 			if (!*cur){
// 				printf("minishell: syntax error: unexpected EOF while looking for matching \'\'\'\n");
// 				break ;
// 			}	
// 		}
// 		if (*cur == '$') // TODO $? $$ $< 등등?
// 		{
// 			tmp = li->content;
// 			li->content = ft_substr(li->content, 0,
// 				cur - (char *)li->content);
// 			while (cur[i] && !ms_isspace(cur[i]) && cur[i] != '\"')
// 				i++;
// 			tmp3 = ft_substr(cur, 1, i - 1);
// 			tmp2 = li->content;
// 			li->content = ft_strjoin(li->content, env_get(m, tmp3));
// 			free(tmp3);
// 			free(tmp2);
// 			tmp2 = li->content;
// 			li->content = ft_strjoin(li->content, cur + i);
// 			free(tmp2);
// 			free(tmp);
// 			cur = (char *)li->content;
// 		}
// 		cur++;
// 	}
// }

// static void	sub_env(t_meta *m)
// {
// 	t_list	*cl;

// 	cl = m->list_args;
// 	while (cl)
// 	{
// 		find_and_sub(m, cl);
// 		cl = cl->next;
// 	}
// }
static char	*find_e(char *str)
{
	while (*str)
	{
		if (*str == '\'')
			ms_skip_quotes(&str, *str);
		else if (*str == '$' && *(str + 1) && !ms_isspace(*(str + 1)))
			return (str);
		str++;
	}
	return (0);
}

// static void	insert_env(t_meta *m, char **str, int ep)
// {
// 	char	*key;
// 	char	*tmp;
// 	char	*env_val;
	
// 	key = ft_strdup(ep);
// 	while (*key && !ms_isspace(*key) && *key != '\'' && *key !='\"')
// 		key++;
// 	*key = '\0';
// 	printf("key: %s\n", key);
// 	env_val = env_get(m, key);
// 	free(key);
// }

static void	stitch(char **s1, char *s2)
{
	char	*os1;
	
	os1 = *s1;
	*s1 = ft_strjoin(*s1, s2);
	free(os1);
}

static void	insert_env(t_meta *m, char **ostr, char **epos)
{
	char	*nstr;
	char	*key;
	char	*env_val;
	char	*orig;
	
	nstr = 0;
	orig = *ostr;
	if (*ostr != *epos)
		nstr = ft_substr(*ostr, 0 , (*epos) - (*ostr));
	*ostr = (*epos)++;
	while (**epos && !ms_isspace(**epos) && **epos != '$' &&
			**epos !='\'' && **epos != '\"')
		(*epos)++;
	key = ms_substr(*ostr, 1, (*epos) - (*ostr) - 1); // TODO branch when key == ?
	env_val = env_get(m, key);
	stitch(&nstr, env_val);
	stitch(&nstr, *epos);
	free(orig);
	free(env_val);
	free(key);
	*ostr = nstr;
}

void	expand(t_meta *m)
{
	t_token	*ct;
	char	*exp;
	char	*cur;

	ct = m->token_start;
	while (ct)
	{
		exp = find_e(ct->str);
		while (exp)
		{
			insert_env(m, &ct->str, &exp);
			exp = find_e(ct->str);
		}
		ct = ct->next;
		// exp = find_e(cur);//ft_strchr(cur, '$');
		// if (exp)
		// {
		// 	if (*(exp + 1) && *(exp + 1) == '?')
		// 	{
		// 		 ; // TODO: replace with exit code
		// 		cur = cur + 1;
		// 	}
		// 	else if (*(exp + 1) && ms_isspace(*(exp + 1)))
		// 	{
		// 		cur = exp + 1;
		// 		continue ;
		// 	}
		// 	insert_env(m, &ct->str, exp);
		// }
		// ct = ct->next;
		// if (ct)
		// 	cur = ct->str;
	}
}