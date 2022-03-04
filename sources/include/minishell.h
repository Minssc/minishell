/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjung <tjung@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 11:56:27 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/04 20:35:45 by tjung            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
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
	int			exit_status;
	t_list		*list_args;
	t_list		*list_env;
}				t_meta;

// env.c
void	env_init(t_meta *m, char **envp);
t_list	*env_find(t_meta *m, char *key);
char	*env_get(t_meta *m, char *key);
int		env_set(t_meta *m, char *key, char *value);

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
void	mexit_pe(int ec);
void	mexit_cm(char *str, int ec);
void	perror_exit(char *str);

// msfunc/ms_trim.c
char	*ms_trim(char *str);

// msfunc/ms_argjoin.c
char	*ms_argjoin(char const *s1, char const *s2);

// msfunc/ms_isspace.c
int		ms_isspace(char c);
int		ms_isemptystr(char *str);

// msfunc/ms_correct.c
int		ms_correct_builtin_cmd(char *bcmd, char *comp);

// msfunc/ms_find.c
t_list	*find_prev_node(t_list *root, t_list *cur_ptr);

// msfunc/ms_custom.c
void	custom_char_free(char *one, char *two);
int		custom_double_char_len(char **ptr);

// signal.c
void	set_signal(void);

// builtin/
int		builtin_pwd(void);
int		builtin_env(char **argu);
int		builtin_unset(char **keys);
int		builtin_export(char **entries);
int		builtin_echo(char **contents);
void	builtin_exit(char **exit_cmd);
int		builtin_cd(char **mv_cmd);

#endif
