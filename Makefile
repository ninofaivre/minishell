# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/24 10:25:16 by nfaivre           #+#    #+#              #
#    Updated: 2021/11/24 16:02:01 by nfaivre          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

all :
	clang -lreadline -Iinclude main.c parsing.c utils.c command.c -o minishell
