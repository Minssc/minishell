/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 15:53:47 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/04 20:19:27 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// token 기준 parsing 
// parsing 후 환경변수 삽입 
// 환경변수 삽입 후 따옴표 제거 

static void	skip_space(char **str)
{
	while (ms_isspace(**str))
		(*str)++;
}

void		ms_skip_quotes(char **str, char quote)
{
	*str = ft_strchr(*str + 1, quote);
	if (!(*str))
		mexit_cm("syntax err \' or \"", 255);
	(*str)++;
}



static void	add_token(t_meta *m, char *from, char *to)
{
	t_token *lt;
	t_token	*nt;

	if (from >= to)
		return ;
	nt = (t_token *)ft_calloc(sizeof(t_token), 1);
	if (!nt)
		perror_exit("ft_calloc failed @add_token");
	nt->str = ft_substr(from, 0, to - from);
	if (!nt->str)
		perror_exit("ft_substr failed @add_token");
	token_add_back(&m->token_start, nt);
}

void	parse(t_meta *m, char *line)
{
	char	*cur;

	skip_space(&line);
	cur = line;
	while (*cur)
	{
		if (*cur == '\"' || *cur == '\'')
			ms_skip_quotes(&cur, *cur);
		else if (*cur == '<' || *cur == '>' || *cur == '|')
		{
			add_token(m, line, cur);
			line = cur++;
			if (*cur && *cur == '<' || *cur == '>')
				add_token(m, line, ++cur);
			else
				add_token(m, line, cur);
			line = cur;
		}
		else if (ms_isspace(*cur))
		{
			add_token(m, line, cur);
			skip_space(&cur);
			line = cur;
		}
		else
			cur++;
	}
	add_token(m, line, cur);
	token_ident_all(m);
	//임시 코드
	t_token *ct = m->token_start;
	// printf("Tokens before expanding\n");
	// while (ct)
	// {
	// 	printf("wat %s\n",ct->str);
	// 	ct = ct->next;
	// }
	// expand(m);

	// printf("\nTokens after expanding\n");
	// ct = m->token_start;
	// while (ct)
	// {
	// 	printf("%s\n",ct->str);
	// 	ct = ct->next;
	// }
	
	unquote(m);
	printf("\nTokens after un-quote\n");
	ct = m->token_start;
	while (ct)
	{
		printf("%s# ident: %u\n",ct->str, ct->type);
		ct = ct->next;
	}

}