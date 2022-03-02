# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: minsunki <minsunki@student.42seoul.kr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/06 13:03:52 by minsunki          #+#    #+#              #
#    Updated: 2021/08/03 15:23:42 by minsunki         ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME		=	libft.a
SRCS		=	ft_atoi.c \
			 	ft_bzero.c \
			 	ft_calloc.c \
			 	ft_isalnum.c \
			 	ft_isalpha.c \
			 	ft_isascii.c \
			 	ft_isdigit.c \
				ft_isprint.c \
				ft_itoa.c \
				ft_memccpy.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_memcpy.c \
				ft_memmove.c \
				ft_memset.c \
				ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putstr_fd.c \
				ft_putstrn_fd.c \
				ft_split.c \
				ft_strchr.c \
				ft_strdup.c \
				ft_strjoin.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_strlen.c \
				ft_strmapi.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strrchr.c \
				ft_strtrim.c \
				ft_substr.c \
				ft_tolower.c \
				ft_toupper.c 

SRCS_B		=	$(SRCS) \
				ft_lstnew.c \
				ft_lstadd_front.c \
				ft_lstsize.c \
				ft_lstadd_back.c \
				ft_lstdelone.c \
				ft_lstclear.c \
				ft_lstiter.c \
				ft_lstmap.c \
				ft_lstlast.c \
				ft_dlstnew.c \
				ft_dlstadd_front.c \
				ft_dlstadd_back.c \
				ft_dlstins_front.c \
				ft_dlstins_back.c \
				ft_dlstsize.c \
				ft_dlstdelone.c \
				ft_dlstclear.c \
				ft_dlstiter.c \
				ft_dlstmap.c \
				ft_dlstlast.c \
				ft_dlstfirst.c \
				get_next_line.c \
				ft_max.c \
				ft_min.c \
				ft_abs.c \
				ft_atol.c \
				ft_isnumstr.c \
				ft_queue.c \
				ft_queue_util.c 

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
OBJS		=	$(SRCS:.c=.o)
OBJS_B		=	$(SRCS_B:.c=.o)
RM			=	rm -f
AR			=	ar rcs

%.o			:	%.c
			$(CC) $(CFLAGS) -c $< -o $@

$(NAME)		:	$(OBJS)
			$(AR) $(NAME) $(OBJS)

bonus		:	$(OBJS_B)
			$(AR) $(NAME) $(OBJS_B)

all			:	$(NAME)

clean		:		
			$(RM) $(OBJS) $(OBJS_B)

fclean		:	clean
			$(RM) $(NAME)

re			:	fclean
			$(MAKE) all

so			:	$(OBJS)
			gcc -nostartfiles -shared -o libft.so $(OBJS)

.PHONY:		all clean fclean .c.o re bonus
