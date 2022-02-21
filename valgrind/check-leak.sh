#!/bin/sh

valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=./valgrind/readline.supp $1 $2 ./minishell
