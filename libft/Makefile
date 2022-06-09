# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: iren <iren@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/09/01 16:49:57 by iren              #+#    #+#              #
#    Updated: 2022/04/30 10:19:22 by iren             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_strlcat.c \
	ft_atoil.c  \
	ft_atoi.c  \
	ft_strlcpy.c \
	ft_bzero.c  \
	ft_strlen.c \
	ft_calloc.c \
	ft_strmapi.c \
	ft_isalnum.c \
	ft_memccpy.c \
	ft_strncmp.c \
	ft_isalpha.c   \
	ft_memchr.c  \
	ft_strnstr.c \
	ft_isascii.c  \
	ft_memcmp.c  \
	ft_strrchr.c \
	ft_isdigit.c  \
	ft_memcpy.c  \
	ft_strtrim.c \
	ft_isprint.c   \
	ft_memmove.c  \
 	ft_substr.c \
	ft_itoa.c   \
	ft_memset.c  \
	ft_tolower.c \
	ft_putchar_fd.c \
   	ft_toupper.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c	\
   	ft_putstr_fd.c   \
	ft_split.c	\
	ft_strchr.c \
	ft_strdup.c	\
	ft_strjoin.c 

SRCS_BONUS = ft_lstnew.c \
			 ft_lstadd_front.c \
			 ft_lstsize.c \
			 ft_lstlast.c \
			 ft_lstadd_back.c \
			 ft_lstdelone.c \
			 ft_lstclear.c \
			 ft_lstiter.c \
			 ft_lstmap.c

OBJS = ${SRCS:.c=.o}

OBJS_BONUS	= ${SRCS_BONUS:.c=.o}

CC	= gcc

CFLAGS	= -Wall -Wextra -Werror

INCLUDE	= libft.h

NAME	= libft.a

all	: ${NAME}

.c.o:
		${CC} -I/${INCLUDE} ${CFLAGS} -c $< -o ${<:.c=.o}
#		${CC} -I/${INCLUDE} ${CFLAGS} -fPIC -g -c $< -o ${<:.c=.o}

$(NAME) : ${OBJS} ${INCLUDE}
	ar rc ${NAME} ${OBJS}
	ranlib ${NAME}

so:
	$(CC) -nostartfiles -fPIC $(CFLAGS) -c $(SRCS)
	gcc -nostartfiles -shared -o libft.so $(OBJS)

bonus	: ${OBJS_BONUS} ${INCLUDE}
	ar rc ${NAME} ${OBJS_BONUS}
	ranlib ${NAME}

clean	:
	rm -f ${OBJS} ${OBJS_BONUS}

fclean	: clean
	rm -f ${NAME}

re:		fclean all
