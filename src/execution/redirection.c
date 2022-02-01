/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:51:18 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/01 19:03:11 by nfaivre          ###   ########.fr       */
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

static int	one_redirection(t_redirection redirection,
int *read_pipe, int *write_pipe, int fd)
{
	if (redirection.guillemet == '<')
	{
		if (read_pipe)
		{
			close(read_pipe[0]);
			read_pipe = (int *) NULL;
		}
		return (take_input(redirection.content, redirection.is_double, fd));
	}
	else if (redirection.guillemet == '>')
	{
		if (write_pipe)
		{
			close(write_pipe[1]);
			write_pipe = (int *) NULL;
		}
		return (take_output(redirection.content, redirection.is_double, fd));
	}
	return (-1);
}

static bool	take_redirection_error(int fd_input, int fd_output)
{
	if (fd_input == -1)
		close(fd_output);
	else if (fd_output == -1)
		close(fd_input);
	return ((bool)(fd_input == -1 || fd_output == -1));
}

bool	take_redirection(t_redirection *redirection,
int *read_pipe, int *write_pipe)
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
			fd_input = one_redirection(redirection[i], read_pipe,
					write_pipe, fd_input);
		if (redirection[i].guillemet == '>')
			fd_output = one_redirection(redirection[i], read_pipe,
					write_pipe, fd_output);
		if (take_redirection_error(fd_input, fd_output))
			return (true);
		i++;
	}
	if (fd_input)
		dup2(fd_input, 0);
	if (fd_output)
		dup2(fd_output, 1);
	return (false);
}
