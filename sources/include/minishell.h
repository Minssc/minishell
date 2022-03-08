/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 11:56:27 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/08 21:15:18 by minsunki         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include "libft.h"
# include "error.h"

// 아래 헤더들 살펴보기

# include <wait.h>
# include <dirent.h>
# include <signal.h>
# include <errno.h>
# include <sys/stat.h>
// libreadline-dev
# include <readline/readline.h>
# include <readline/history.h>

# define Q_DQ 0b01
# define Q_SQ 0b10

//Token Type
// EMPTY, COMMAND, ARGUMENT, PIPE, APPEND LEFT/RIGHT, INPUT, REDIRECTION LEFT/RIGHT

# define T_EMP	0b00000000
# define T_CMD	0b00000001
# define T_ARG	0b00000010
# define T_PIP	0b00000100
# define T_APL	0b00001000
# define T_APR	0b00010000
# define T_RDR	0b00100000
# define T_RDL	0b01000000
# define REDIR	0b01111000
# define DELIM	0b01111100

# define B_CD	0b00000001
# define B_ECHO	0b00000010
# define B_ENV	0b00000100
# define B_EXIT	0b00001000
# define B_EXPT	0b00010000
# define B_PWD	0b00100000
# define B_UNST	0b01000000

# define S_FLAG (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

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
	char		*line;
	int			stop;
	int			stdin;
	int			stdout;
	int			fd_in;
	int			fd_out;
	int			pipe[2];
	int			pid;
	int			child;
	int			hd_cur;
	int			waiting;
}				t_meta;

typedef unsigned char	t_byte;


// fd.c
void	fd_close(int fd);
void	fd_reset(t_meta *m);
void	fd_destroy(t_meta *m);
void	fd_reset_std(t_meta *m);

// meta.c
t_meta	*meta_get(void);
t_meta	*meta_init(void);
void	meta_destroy(void);

// mexit.c
void	mexit(int ec);
void	mexit_pe(int ec);
void	mexit_cm(char *str, int ec);
void	perror_exit(char *str);

// signal.c
void	set_signal(void);

//redir/
// redir.c
void	redir_r(t_meta *m, t_token *tok, t_byte type);
void	redir_l(t_meta *m, t_token *tok, t_byte type);
int		redir_p(t_meta *m, t_token *tok);

// heredoc.c
void	heredoc_init(t_meta *m);
char	*heredoc_getname(int num);

// heredoc_util.c
char	*heredoc_getname(int num);
void	heredoc_read(t_meta *m, char *tstr, int fd);


//exec/
// exec.c
void	exec_start(t_meta *m);

// bin.c
int		bin_run(t_meta *m, char *bin);

// bin_util.c
char	*bin_find(t_meta *m, char *bin);

// argv.c
char	**argv_build(t_token *tok);
void	argv_destroy(t_meta *m);

// exec_util.c
t_token	*next_cmd(t_token *tok);
int		is_builtin(char *bin);

//token/
// token.c
void	token_add_back(t_token **th, t_token *nt);
void	token_destroy(t_meta *m);
void	token_parse(t_meta *m, char *from, char *to);

// token_util.c
t_byte	token_ident(t_token *tok);
t_token	*token_prev_delim(t_token *tok);
t_token	*token_next_delim(t_token *tok);

//env/
// env.c
void	env_init(t_meta *m, char **envp);
char	**env_build(t_meta *m);
void	env_destroy(t_meta *m);

// env_util.c
t_list	*env_find(t_meta *m, char *key);
char	*env_get(t_meta *m, char *key);
int		env_set(t_meta *m, char *key, char *value);

//parse/
// parse/parse.c
void	parse(t_meta *m, char *line);
void	ms_skip_quotes(char **str, char quote);

// parse/ourt.c
void	sort_tokens(t_meta *m);

// parse/expand.c
void	insert_env(t_meta *m, char **ostr, char **epos);
void	expand(t_meta *m);

// parse/expand_util.c
char	*find_e(char *str);

// cleanup.c
void	cleanup(t_meta *m);

//msfunc/
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

// msfunc/ms_find.c
t_list	*find_prev_node(t_list *root, t_list *cur_ptr);

// msfunc/ms_custom.c
void	custom_char_free(char *one, char *two);
int		custom_double_char_len(char **ptr);
int		custom_perr_and_set_exnum(char *str, int exnum, char *heap, int ret);
int		custom_putendl(char *str, int ret);

// msfunc/ms_stitch.c
void	ms_stitch(char **s1, char *s2);

// msfunc/ms_puterr.c
void	ms_puterr(char *type, char *msg);

//builtin/
// builtin/pwd.c
int		builtin_pwd(void);

// builtin/env.c
int		builtin_env(char **argu);

// builtin/unset.c
int		builtin_unset(char **keys);

// builtin/export.c
int		builtin_export(char **entries);

// builtin/echo.c
int		builtin_echo(char **contents);

// builtin/exit.c
void	builtin_exit(char **exit_cmd);

// builtin/cd.c
int		builtin_cd(char **mv_cmd);

#endif
