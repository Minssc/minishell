/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 11:56:27 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/02 17:50:13 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h
# include <signal.h>
# include "libft.h"

// 아래 헤더들 살펴보기

# include <signal.h>
# include "libft.h"
// libreadline-dev
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_meta
{
	t_list	*list_args;
}				t_meta;

// parse.c
void	parse(t_meta *m, char *line);

// minishell.c
int		ms_loop(t_meta *m);

// meta.c
t_meta	*meta_get(void);
t_meta	*meta_init(void);
void	meta_destroy(void);

// mexit.c
void	mexit(int ec);
void	perror_exit(char *str);

// msfunc/ms_trim.c
char	*ms_trim(char *str);

// msfunc/ms_argjoin.c
char	*ms_argjoin(char const *s1, char const *s2);
typedef struct s_env {
	char			*contents;
	struct s_env	*prev;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd {
	char	**parts;
	int		pipe;
	int		redir;
}	t_cmd;

typedef struct s_input {
	struct s_cmd	*cmd_list;
	struct s_input	*next;
}	t_input;

typedef struct s_info {
	struct s_env	*n_env;
	struct s_input	*chunks;
	char			*input;
}	t_info;

int	g_exit_status;

/*
 *			ft_lst_env.c
 */
t_env		*ft_lstnew_env(void);
int			ft_lstsize_env(t_env *lst);
t_env		*ft_lstlast_env(t_env *lst);
void		ft_lstadd_back_env(t_env **lst, t_env *new);
void		ft_lstdelone_env(t_env *lst);

/*
 *			ft_isspace.c
 */
int			ft_isspace(char *str);

/*
 *			signal.c
 */
void		set_signal(void);

/*
 *			builtin func
 */
int			mini_pwd(void);
int			mini_env(t_env *root);
int			mini_unset(t_env *target, char *key);
int			mini_echo(char **argu);

#endif
