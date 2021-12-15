# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/24 10:25:16 by nfaivre           #+#    #+#              #
#    Updated: 2021/12/15 13:14:29 by nfaivre          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL = all

NAME = minishell

CC = clang
CFLAGS = -Wall -Werror -Wextra

DIR_SRC = src
DIR_OBJ = .obj

INCLUDE = -Iinclude

SRC = $(wildcard $(DIR_SRC)/*/*.c)
OBJ = $(addprefix $(DIR_OBJ)/, $(notdir $(SRC:.c=.o)))

mkdir_DIR_OBJ:
	mkdir -p $(DIR_OBJ)

$(DIR_OBJ)/%.o : $(DIR_SRC)/*/%.c ./include/header.h
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDE)

$(NAME):
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) -lreadline

all: mkdir_DIR_OBJ $(OBJ) $(NAME)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -rf $(DIR_OBJ)

re: fclean all

.PHONY: all clean fclean re