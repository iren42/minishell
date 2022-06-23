# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iren <iren@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/15 17:41:07 by iren              #+#    #+#              #
#    Updated: 2022/06/23 17:22:02 by gufestin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

LIBFT	= libft

HEADER	= include/minishell.h

DIR_SOURCES	= src/

SOURCES		=	minishell.c \
				signal_handler.c \
				ft_error.c \
				\
				parser/lexer.c \
				parser/lexer_utils.c \
				parser/parser.c \
				parser/get_cmd.c \
				\
				expander/expander.c \
				expander/var_substitution.c \
				expander/rm_superflous.c \
				\
			executor/executor.c \
			executor/pipes_utils.c \
				\
			heredoc.c \
				\
				builtin/ft_pwd.c \
				builtin/ft_env.c \
				builtin/ft_export.c \
				builtin/ft_unset.c \
				builtin/ft_exit.c \
				builtin/ft_cd.c\
				builtin/ft_echo.c\
				\
				util/t_quote_utils.c \
				util/t_cmdtab_utils.c \
				util/t_env_utils.c \
				util/t_token_utils.c \
				util/t_redir_utils.c \
				util/t_arg_utils.c \
				util/free.c \
				util/print.c \
				


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
