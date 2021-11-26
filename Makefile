# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/24 10:25:16 by nfaivre           #+#    #+#              #
#    Updated: 2021/11/26 14:34:20 by nfaivre          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL = all

NAME = minishell

CC = clang
CFLAGS = -Wall -Werror -Wextra

DIR_SRC = src
DIR_OBJ = .obj

INCLUDE = -Iinclude

SRC = $(wildcard $(DIR_SRC)/*.c)
OBJ = $(addprefix $(DIR_OBJ)/, $(subst src/,, $(SRC:.c=.o)))

$(DIR_OBJ)/%.o : $(DIR_SRC)/%.c ./include/header.h
	@mkdir -p $(DIR_OBJ)
	$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDE)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -lreadline $(OBJ) -o $(NAME)

all: $(OBJ) $(NAME)

clean:
	@rm -rf $(OBJ)
	@echo "removing $(OBJ)"

fclean: clean
	@rm -rf $(NAME)
	@echo "removing $(NAME)"

re: fclean all

.PHONY: all clean re fclean