/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 18:26:43 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/22 16:43:15 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <errno.h>

static char	**get_doubleinput(char *eof)
{
	char	**doubleinput;
	char	*input;

	doubleinput = NULL;
	input = readline(">");
	while (!is_same_string(input, eof) && input)
	{	
		doubleinput = add_str_to_str_tab(doubleinput, input);
		if (!doubleinput)
		{
			minishell_error("execution (here-doc)", NULL, ALLOC);
			free(input);
			return (NULL);
		}
		input = readline(">");
	}
	if (input)
		free(input);
	return (doubleinput);
}

static int	take_doubleinput(char *eof)
{
	int		pipe_tab[2];
	char	**doubleinput;

	if (pipe(pipe_tab) == -1)
	{
		pipe_error("execution (here-doc)", NULL);
		return (-1);
	}
	doubleinput = get_doubleinput(eof);
	if (!doubleinput)
		return (-1);
	write_str_tab_to_fd(doubleinput, pipe_tab[1]);
	close(pipe_tab[1]);
	free_str_tab(&doubleinput);
	return (pipe_tab[0]);
}

int	take_input(char *content, bool is_double, int fd_input)
{
	int	fd;

	fd = 0;
	if (fd_input)
		close(fd_input);
	if (is_double == true)
		fd = take_doubleinput(content);
	else if (access(content, R_OK) == -1)
	{
		if (access(content, F_OK) != -1)
			minishell_error(NULL, content, RIGHT);
		else
			minishell_error(NULL, content, INACCESSIBLE);
		return (-1);
	}
	else
	{
		fd = open(content, O_RDONLY);
		if (fd == -1)
			minishell_error(NULL, content, INACCESSIBLE);
	}
	return (fd);
}

int	take_output(char *content, bool is_double, int fd_output)
{
	int	fd;

	fd = 0;
	if (fd_output)
		close(fd_output);
	if (access(content, F_OK) != -1 && access(content, W_OK) == -1)
	{
		minishell_error(NULL, content, RIGHT);
		return (-1);
	}
	if (is_double == true)
		fd = open(content, O_APPEND | O_WRONLY | O_CREAT, 0644);
	else
		fd = open(content, O_TRUNC | O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		minishell_error(NULL, content, CREAT);
	return (fd);
}
