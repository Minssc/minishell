# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/22 23:04:25 by minsunki          #+#    #+#              #
#    Updated: 2022/03/04 17:37:11 by minsunki         ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

SRCF		=	sources
SRCF_B		=	bonus

BI			=	builtin/

FIL_M		=	main \
				env \
				meta \
				mexit \
				minishell \
				signal \
				parse \
				syntax \
				expand \
				unquote \
				token \
				exec \
				argv \
				msfunc/ms_trim \
				msfunc/ms_argjoin \
				msfunc/ms_isspace \
				msfunc/ms_substr 

FIL_B		=

SRCS_M		=	$(addsuffix .c, $(addprefix $(SRCF)/, $(FIL_M)))
SRCS_B		=	$(addsuffix _bonus.c, $(addprefix $(SRCF_B)/, $(FIL_M) $(FIL_B)))

OBJS_M		=	$(SRCS_M:.c=.o)
OBJS_B		=	$(SRCS_B:.c=.o)

CC			=	gcc
# CFLAGS		=	-Wall -Wextra -Werror
CFLAG_EXT	=	-L/usr/lib -lreadline \
				-Llibft -lft \

CFLAG_INCL	=	-Ilibft -Isources/include -Ibonus/include

RM			=	rm -f

# LIB_NAME		=	readline
# LIB_HEADER		=	/usr/local/opt/readline/include/
#  LIB_FOLDER		=	/usr/local/opt/readline/lib/

%.o			:	%.c
			$(CC) $(CFLAGS) $(CFLAG_INCL) -c $< -o $@

$(NAME)		:	$(OBJS_M)
			make bonus -C libft
			$(CC) $(OBJS_M) $(CFLAG) $(CFLAG_EXT) $(CFLAG_INCL) -o $(NAME)


bonus		:	$(OBJS_B)
			make bonus -C libft
			$(CC) $(OBJS_B) $(CFLAG) $(CFLAG_EXT) $(CFLAG_INCL)-o $(NAME)

clean		:
			$(RM) $(OBJS_M) $(OBJS_B)
			make clean -C libft

all			:	$(NAME)

fclean		:	clean
			$(RM) $(NAME)
			make fclean -C libft

re			:	fclean all

.PHONY		:	.c.o all clean fclean re bonus
