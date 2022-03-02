/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 11:56:27 by minsunki          #+#    #+#             */
/*   Updated: 2022/03/02 14:59:40 by minsunki         ###   ########seoul.kr  */
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
// libreadline-dev
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_meta
{
	
}				t_meta;

// minishell.c
int		ms_loop(t_meta *m);

// meta.c
t_meta	*meta_get(void);
t_meta	*meta_init(void);
void	meta_destroy(void);

// mexit.c
void	mexit(int ec);
void	perror_exit(char *str);

# endif