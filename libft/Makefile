# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aleduc <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/13 16:40:19 by aleduc            #+#    #+#              #
#    Updated: 2018/09/18 02:51:10 by aleduc           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC_PATH = ./
OBJ_PATH = obj/
SRC_NAME = ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memchr.c ft_memcmp.c \
			ft_memset.c ft_memmove.c ft_strcat.c ft_strchr.c ft_strcpy.c \
			ft_strdup.c ft_strlcat.c ft_strlen.c ft_strncat.c ft_strncpy.c \
			ft_atoi.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c \
			ft_isprint.c ft_strnstr.c ft_strstr.c ft_strrchr.c ft_tolower.c \
			ft_toupper.c ft_strcmp.c ft_strncmp.c ft_memalloc.c ft_strnew.c \
			ft_memdel.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c \
			ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c \
			ft_strjoin.c ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			ft_strtrim.c ft_strsplit.c ft_itoa.c ft_lstnew.c ft_lstdelone.c \
			ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_isspace.c \
			ft_strrev.c ft_swap.c ft_sort_integer_table.c ft_lsttail.c \
			get_next_line.c ft_split_whitespaces.c ft_lstsize.c ft_fill_str.c
OBJ_NAME = $(SRC_NAME:.c=.o)
SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c libft.h
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: all, clean, fclean, re

clean :
	@/bin/rm -f $(OBJ)

fclean : clean
	@/bin/rm -f $(NAME)
	@echo "\033[1;30mLibrairie detruite.\033[0m"

re : fclean all

norme :
	@norminette $(SRC_PATH) $(OBJ_PATH)
