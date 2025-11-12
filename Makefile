# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dhde-lim <dhde-lim@student.42.rio>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/20 17:42:43 by dhde-lim          #+#    #+#              #
#    Updated: 2025/11/12 02:07:08 by dhde-lim         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# CONFIG

NAME 		= libft.a

CC 			= cc
CFLAGS		= -Wall -Werror -Wextra
CPPFLAGS	= -I.

SRCS		= 	ft_isalpha.c	\
				ft_isascii.c	\
				ft_isalnum.c	\
				ft_isdigit.c	\
				ft_isprint.c	\
				ft_toupper.c	\
				ft_tolower.c	\
				ft_strlen.c		\
				ft_memset.c		\
				ft_bzero.c		\
				ft_memcpy.c		\
				ft_memmove.c	\
				ft_strlcpy.c	\
				ft_strlcat.c	\
				ft_strchr.c		\
				ft_strrchr.c	\
				ft_strncmp.c	\
				ft_memchr.c		\
				ft_memcmp.c		\
				ft_strnstr.c	\
				ft_strdup.c		\
				ft_atoi.c		\
				ft_calloc.c		\
				ft_substr.c		\
				ft_strjoin.c	\
				ft_strtrim.c	\
				ft_split.c		\
				ft_itoa.c		\
				ft_strmapi.c	\
				ft_striteri.c	\
				ft_putchar_fd.c	\
				ft_putstr_fd.c	\
				ft_putendl_fd.c	\
				ft_putnbr_fd.c	

OBJS		= $(SRCS:.c=.o)

# TARGET

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o ${<:.c=.o}

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

# Makefile should never use the names below as files, but rather as 
# the defined commands. 
.PHONY: all clean fclean re
