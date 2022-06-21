# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iren <iren@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/15 17:41:07 by iren              #+#    #+#              #
#    Updated: 2022/06/21 01:20:28 by isabelle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

LIBFT	= libft

HEADER	= include/minishell.h

DIR_SOURCES	= src/

SOURCES		=	minishell.c \
				print.c \
				parser/lexer.c \
				parser/parser.c \
				ft_splitsh.c \
				ft_error.c \
				parser/get_cmd.c \
				free.c \
				expander/expander.c \
				expander/var_substitution.c \
				expander/rm_superflous.c \
				signal_handler.c \
				builtin/ft_pwd.c \
				builtin/ft_env.c \
				builtin/ft_export.c
				


SRCS	=	$(addprefix $(DIR_SOURCES), $(SOURCES))

OBJS	= $(SRCS:.c=.o)

CC		= gcc

CFLAGS	= 
#-Wall -Wextra -Werror

SANI	= -fsanitize=address -g3

RM		= rm -f

all		: $(NAME)

%.o		: %.c $(HEADER)
		$(CC) $(CFLAGS) $(SANI) -g3 -Iinclude -c $< -o $@

$(NAME) : $(OBJS) $(HEADER) $(LIBFT)
		make -C $(LIBFT)
		make bonus -C $(LIBFT)
	  	$(CC) $(SANI) -o  $@ $(OBJS) -lreadline libft/libft.a
	

norm	:
		norminette $(SRCS)
		norminette $(HEADER)

clean	:
		$(RM) $(OBJS)
		make clean -C $(LIBFT)

fclean	: clean
		make fclean -C $(LIBFT)
		$(RM) $(NAME)

re		: fclean all

.PHONY:	all clean fclean re
