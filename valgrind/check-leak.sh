#!/bin/sh

valgrind --leak-check=full --show-leak-kinds=all --suppressions=./valgrind/readline.supp ./minishell
