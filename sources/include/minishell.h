/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 11:56:27 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/05 15:55:00 by minsunki         ###   ########seoul.kr  */
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

# include <wait.h>
# include <dirent.h>
# include <signal.h>
# include <errno.h>
# include "libft.h"
// libreadline-dev
# include <readline/readline.h>
# include <readline/history.h>

# define QUOTES_DQ 0b01;
# define QUOTES_SQ 0b10;

//Token Type
// EMPTY, COMMAND, ARGUMENT, PIPE, APPEND LEFT/RIGHT, INPUT, REDIRECTION LEFT/RIGHT

# define T_EMP 0b00000000
# define T_CMD 0b00000001
# define T_ARG 0b00000010
# define T_PIP 0b00000100
# define T_APL 0b00001000
# define T_APR 0b00010000
# define T_INP 0b00100000
# define T_RDR 0b01000000
# define T_RDL 0b10000000

# define B_CD	0b00000001
# define B_ECHO	0b00000010
# define B_ENV	0b00000100
# define B_EXIT	0b00001000
# define B_EXPT	0b00010000
# define B_PWD	0b00100000
# define B_UNST	0b01000000

typedef struct s_token
{
	char			*str;
	unsigned char	type;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_meta
{
	int			exit_status;
	t_token		*token_start;
	t_list		*list_env;
	char		**argv;
	int			p_in;
	int			p_out;
	int			in;
	int			out;
	int			pid;
}				t_meta;

typedef unsigned char t_byte;

// bin.c
char	*bin_find(t_meta *m, char *bin);
int		bin_run(t_meta *m, char *bin);
// int		execute_bin(t_meta *m);

// argv.c
char	**argv_build(t_token *tok);
void	argv_destroy(t_meta *m);

// exec.c
void	exec_start(t_meta *m);

// token.c
int		token_istype(t_token *tok, char *str);
void	token_ident_all(t_meta *m);
t_byte	token_ident(t_token *tok);
void	token_add_back(t_token **th, t_token *nt);
void	token_del(t_token *tok);

// unquote.c
void	unquote(t_meta *m);

// expand.c
void	expand(t_meta *m);

// env.c
void	env_init(t_meta *m, char **envp);
char	**env_build(t_meta *m);
t_list	*env_find(t_meta *m, char *key);
char	*env_get(t_meta *m, char *key);
int		env_set(t_meta *m, char *key, char *value);

// parse.c
void	parse(t_meta *m, char *line);
void	ms_skip_quotes(char **str, char quote);

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

// msfunc/ms_free.c
void	ms_free_dca(char ***dca);
void	ms_free(void **ptr);

// msfunc/ms_substr.c
char	*ms_substr(char const *s, unsigned int start, int len);

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
int		custom_perr_and_set_exnum(char *str, int exnum, char *heap, int ret);

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
