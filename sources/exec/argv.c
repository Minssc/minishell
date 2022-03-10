/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 17:36:57 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/10 22:52:17 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// count the number of argument types for build_argv.

static int	get_nargs(t_token *tok)
{
	t_token	*ct;
	int		ret;

	ct = tok->next;
	ret = 1;
	while (ct)
	{
		if (token_ident(ct) == T_ARG)
			ret++;
		else
			return (ret);
		ct = ct->next;
	}
	return (ret);
}

// builds arguemnt vector to be used in execution.
// TODO make an adaquate free function for argv.
// iterate through the tokens until end of ARG type tokens.
// const inst nargs to preserve precious line.

char	**argv_build(t_token *tok)
{
	char		**ret;
	t_token		*ct;
	const int	nargs = get_nargs(tok);
	int			i;

	ct = tok;
	ret = (char **)ft_calloc(sizeof(char *), (nargs + 1));
	if (!ret)
		perror_exit("ft_calloc failed for ret @build_argv");
	i = -1;
	while (++i < nargs)
	{
		ret[i] = ft_strdup(ct->str);
		ct = ct->next;
	}
	return (ret);
}

// frees argv array.
// remember to zero the argv afterwards as a good habbit.

void	argv_destroy(t_meta *m)
{
	char	**argv;

	if (!m->argv)
		return ;
	argv = m->argv;
	while (*argv)
	{
		if (*argv)
			free(*argv);
		argv++;
	}
	free(m->argv);
	m->argv = 0;
}
