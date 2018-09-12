# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aleduc <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/13 16:40:19 by aleduc            #+#    #+#              #
#    Updated: 2018/09/12 12:26:52 by aleduc           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC_PATH = srcs/
OBJ_PATH = obj/
SRC_NAME = main.c env.c read.c lexer.c built_in.c free.c list.c list_2.c dir.c
OBJ_NAME = $(SRC_NAME:.c=.o)
SRC = $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH),$(OBJ_NAME))
CC = gcc
CFLAGS = -Wall -Wextra -Werror

all : $(NAME)

$(NAME) : $(OBJ)
	@make -C libft/
	@printf "\r\033[K""\r\033[K""\033[32mCompilation...\033[0m"
	@$(CC) $(CFLAGS) $(OBJ) -Llibft/ -lft -Ilibft/ -Iincludes/ -o $(NAME)
	@printf "\r\033[K""\r\033[K""\033[32mCompilation terminee !\033[0m\n"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c libft/libft.h includes/minishell.h
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -o $@ -c $< -Ilibft/ -Iincludes
	@printf "\033[42m \033[0m"

.PHONY: all, clean, fclean, re

clean :
	@/bin/rm -f $(OBJ)
	@make -C libft/ clean
	@echo "\033[1;30mFichier .o supprime.\033[0m"

fclean : clean
	@/bin/rm -f $(NAME)
	@make -C libft/ fclean
	@echo "\033[1;30mExecutable detruit.\033[0m"

re : fclean all

norme :
	@norminette $(SRC_PATH) $(OBJ_PATH)
