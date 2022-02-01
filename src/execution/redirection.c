/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:51:18 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/01 16:24:28 by nfaivre          ###   ########.fr       */
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

static int	doubleinput(char *eof)
{
	int		pipe_tab[2];
	char	**str_tab;
	char	*input;

	str_tab = (char **) NULL;
	input = readline(">");
	while (!is_same_string(input, eof) && input)
	{
		str_tab = add_str_to_str_tab(str_tab, input);
		if (!str_tab)
		{
			minishell_error("execution (here-doc)", (char *) NULL, ALLOC);
			free(input);
			return (-1);
		}
		input = readline(">");
	}
	if (pipe(pipe_tab) == -1)
	{
		if (errno == EMFILE)
			minishell_error("execution (here-doc)", (char *) NULL, MAXFDPROC);
		else if (errno == ENFILE)
			minishell_error("execution (here-doc)", (char *) NULL, MAXFDSYS);
		pipe_tab[0] = -1;
	}
	else
	{
		write_str_tab_to_fd(str_tab, pipe_tab[1]);
		close(pipe_tab[1]);
	}
	free_str_tab(str_tab);
	free(input);
	return (pipe_tab[0]);
}

static int	take_input(char *content, bool is_double, int fd_input)
{
	int	fd;

	fd = 0;
	if (fd_input)
		close(fd_input);
	if (is_double == true)
		fd = doubleinput(content);
	else if (access(content, R_OK) == -1)
	{
		minishell_error((char *) NULL, content, INACCESSIBLE);
		return (-1);
	}
	else
		fd = open(content, O_RDONLY);
	if (fd == -1)
		minishell_error((char *) NULL, content, INACCESSIBLE);
	return (fd);
}

static int	take_output(char *content, bool is_double, int fd_output)
{
	int	fd;

	fd = 0;
	if (fd_output)
		close(fd_output);
	if (is_double == true)
		fd = open(content, O_APPEND | O_RDWR | O_CREAT, 0644);
	else
		fd = open(content, O_TRUNC | O_RDWR | O_CREAT, 0644);
	if (fd == -1)
		minishell_error((char *) NULL, content, CREAT);
	return (fd);
}

bool	take_redirection(t_redirection *redirection, int *read_pipe, int *write_pipe)
{
	int	fd_input;
	int	fd_output;
	int	i;

	fd_input = 0;
	fd_output = 0;
	i = 0;
	while (redirection[i].content)
	{
		if (redirection[i].guillemet == '<')
		{
			if (read_pipe)
			{
				close(read_pipe[0]);
				read_pipe = (int *) NULL;
			}
			fd_input = take_input(redirection[i].content, redirection[i].is_double, fd_input);
			if (fd_input == -1)
				return (true);
		}
		else if (redirection[i].guillemet == '>')
		{
			if (write_pipe)
			{
				close(write_pipe[1]);
				write_pipe = (int *) NULL;
			}
			fd_output = take_output(redirection[i].content, redirection[i].is_double, fd_output);
			if (fd_output == -1)
				return (true);
		}
		i++;
	}
	if (fd_input)
		dup2(fd_input, 0);
	if (fd_output)
		dup2(fd_output, 1);
	return (false);
}