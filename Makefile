# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/22 23:04:25 by minsunki          #+#    #+#              #
#    Updated: 2022/03/09 16:24:51 by minsunki         ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

SRCF		=	sources
SRCF_B		=	bonus

BI			=	builtin/

FIL_M		=	main \
				meta \
				mexit \
				signal \
				syntax \
				fd \
				redir/redir \
				redir/heredoc \
				redir/heredoc_util \
				exec/exec \
				exec/exec_util \
				exec/argv \
				exec/bin \
				exec/bin_util \
				token/token \
				token/token_util \
				env/env \
				env/env_util \
				parse/parse \
				parse/sort \
				parse/expand \
				parse/expand_util \
				parse/cleanup \
				msfunc/ms_set_es \
				msfunc/ms_trim \
				msfunc/ms_argjoin \
				msfunc/ms_isspace \
				msfunc/ms_substr \
				msfunc/ms_free \
				msfunc/ms_find \
				msfunc/ms_custom \
				msfunc/ms_stitch \
				msfunc/ms_puterr \
				builtin/pwd \
				builtin/env \
				builtin/unset \
				builtin/export \
				builtin/echo \
				builtin/exit \
				builtin/cd

FIL_B		=

FIL_HDOC	=	/tmp/minishell_heredoc_*

SRCS_M		=	$(addsuffix .c, $(addprefix $(SRCF)/, $(FIL_M)))
SRCS_B		=	$(addsuffix _bonus.c, $(addprefix $(SRCF_B)/, $(FIL_M) $(FIL_B)))

OBJS_M		=	$(SRCS_M:.c=.o)
OBJS_B		=	$(SRCS_B:.c=.o)

CC			=	gcc
# CFLAGS		=	-Wall -Wextra -Werror
CFLAG_EXT	=	-Llibft -lft \
				-Lreadline-master -lreadline -lhistory \
				-ltermcap

CFLAG_INCL	=	-Ilibft -Isources/include -Ibonus/include

RM			=	rm -f

%.o			:	%.c
			$(CC) $(CFLAGS) $(CFLAG_INCL) -c $< -o $@

$(NAME)		:	$(OBJS_M)
			make bonus -j16 -C libft
			$(RM) $(FIL_HDOC)
			$(CC) $(OBJS_M) $(CFLAG) $(CFLAG_EXT) $(CFLAG_INCL) -o $(NAME)


bonus		:	$(OBJS_B)
			make bonus -C libft
			$(RM) $(FIL_HDOC)
			$(CC) $(OBJS_B) $(CFLAG) $(CFLAG_EXT) $(CFLAG_INCL)-o $(NAME)

clean		:
			$(RM) $(OBJS_M) $(OBJS_B) $(FIL_HDOC)
			make clean -C libft

all			:	$(NAME)

fclean		:	clean
			$(RM) $(NAME)
			make fclean -C libft

re			:	fclean all

.PHONY		:	.c.o all clean fclean re bonus
