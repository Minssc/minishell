# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/22 23:04:25 by minsunki          #+#    #+#              #
#    Updated: 2022/03/02 13:38:11 by minsunki         ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell

SRCF		=	sources
SRCF_B		=	bonus

FIL_M		=	main \
				meta \
				mexit

FIL_B		=	

SRCS_M		=	$(addsuffix .c, $(addprefix $(SRCF)/, $(FIL_M)))
SRCS_B		=	$(addsuffix _bonus.c, $(addprefix $(SRCF_B)/, $(FIL_M) $(FIL_B)))

OBJS_M		=	$(SRCS_M:.c=.o)
OBJS_B		=	$(SRCS_B:.c=.o)

CC			=	gcc
# CFLAGS		=	-O3 -Wall -Wextra -Werror
CFLAG_EXT	=	-L/usr/lib -lreadline \
				-Llibft -lft \

CFLAG_INCL	=	-Ilibft -Isources/include -Ibonus/include

RM			=	rm -f

%.o			:	%.c
			$(CC) $(CFLAGS) $(CFLAG_INCL) -c $< -o $@

$(NAME)		:	$(OBJS_M)
			make all -C libft
			$(CC) $(OBJS_M) $(CFLAG) $(CFLAG_EXT) $(CFLAG_INCL) -o $(NAME)

bonus		:	$(OBJS_B)
			make all -C libft
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
