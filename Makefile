# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iren <iren@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/15 17:41:07 by iren              #+#    #+#              #
#    Updated: 2022/06/09 15:15:33 by iren             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

LIBFT	= libft

HEADER	= include/minishell.h

DIR_SOURCES	= src/

SOURCES		=	minishell.c \
				print.c \
				lexer.c
				


SRCS	=	$(addprefix $(DIR_SOURCES), $(SOURCES))

OBJS	= $(SRCS:.c=.o)

CC		= gcc

CFLAGS	= 
#-Wall -Wextra -Werror

SANI	= -fsanitize=address -g3

RM		= rm -f

all		: $(NAME)

%.o		: %.c $(HEADER) $(LIBFT)
		$(CC) $(CFLAGS) -Iinclude -c $< -o $@
#		$(CC) $(CFLAGS) $(SANI) -Iinclude -c $< -o $@

$(NAME) : $(OBJS) $(HEADER) $(LIBFT)
		make -C $(LIBFT)
		make bonus -C $(LIBFT)
	  	$(CC) -o $@ $(OBJS) -lreadline libft/libft.a
#	  	$(CC) $(SANI) -o $@ $(OBJS) -lreadline
	

norm	:
		norminette $(SRCS)
		norminette $(HEADER)

clean	:
		$(RM) $(OBJS)
		make clean -C $(LIBFT)

fclean	: clean
		$(RM) $(NAME)

re		: fclean all

.PHONY:	all clean fclean re
