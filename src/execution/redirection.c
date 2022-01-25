/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:51:18 by nfaivre           #+#    #+#             */
/*   Updated: 2022/01/25 15:20:55 by nfaivre          ###   ########.fr       */
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

static int	doubleinput_return(int *pipe_tab, char **str_tab,
bool need_pipe, char *input)
{
	if (need_pipe == false)
	{
		free_str_tab(str_tab);
		free(input);
		return (0);
	}
	else
	{
		pipe(pipe_tab);
		write_str_tab_to_fd(str_tab, pipe_tab[1]);
		close(pipe_tab[1]);
		free_str_tab(str_tab);
		free(input);
		return (pipe_tab[0]);
	}
}

static int	doubleinput(char *eof, bool need_pipe)
{
	int		pipe_tab[2];
	char	**str_tab;
	char	*input;

	str_tab = (char **) NULL;
	input = readline(">");
	while (!is_same_string(input, eof))
	{
		str_tab = add_str_to_str_tab(str_tab, input);
		input = readline(">");
	}
	return (doubleinput_return(pipe_tab, str_tab, need_pipe, input));
}

bool	take_input(t_redirection *input, int *read_pipe)
{
	int	fd;
	int	i;

	i = -1;
	if (read_pipe)
		close(read_pipe[0]);
	while (input[++i].content)
	{
		if (input[i].is_double == true)
		{
			fd = doubleinput(input[i].content, !input[i + 1].content);
			if (fd != -1 && !input[i + 1].content)
				dup2(fd, 0);
		}
		else if (access(input[i].content, R_OK) == -1)
			return (minishell_error(input[i].content, INACCESSIBLE) + true);
		else if (!input[i + 1].content)
		{
			fd = open(input[i].content, O_RDONLY);
			dup2(fd, 0);
			break ;
		}
	}
	return (false);
}

bool	take_output(t_redirection *output, int *write_pipe)
{
	int	fd;
	int	i;

	i = 0;
	if (write_pipe)
		close(write_pipe[1]);
	while (output[i].content)
	{
		if (output[i].is_double == true)
			fd = open(output[i].content, O_APPEND | O_RDWR | O_CREAT, 0644);
		else
			fd = open(output[i].content, O_TRUNC | O_RDWR | O_CREAT, 0644);
		if (fd != -1)
		{
			if (!output[i + 1].content)
				dup2(fd, 1);
			else
				close(fd);
		}
		else
			return (minishell_error(output[i].content, CREAT) + true);
		i++;
	}
	return (false);
}
