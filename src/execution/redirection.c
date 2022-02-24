/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:51:18 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/24 16:02:29 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <stdlib.h>

static int	one_redirection(t_redirection redirection,
int *read_pipe, int *write_pipe, int fd)
{
	if (redirection.guillemet == '<')
	{
		if (read_pipe)
		{
			close(read_pipe[0]);
			read_pipe = NULL;
		}
		return (take_input(redirection.content, fd));
	}
	else if (redirection.guillemet == '>')
	{
		if (write_pipe)
		{
			close(write_pipe[1]);
			write_pipe = NULL;
		}
		return (take_output(redirection.content, redirection.is_double, fd));
	}
	return (-1);
}

static bool	take_redirection_error(int fd_input, int fd_output)
{
	if (fd_input == -1 && fd_output)
		close(fd_output);
	else if (fd_output == -1 && fd_input)
		close(fd_input);
	return ((bool)(fd_input == -1 || fd_output == -1));
}

static void	take_redirection_dupe(int *pipe, int fd, int duped, bool is_child)
{
	if (fd && is_child)
		dup2(fd, duped);
	else if (is_child)
	{
		if (pipe)
			dup2(pipe[duped], duped);
	}
	else if (fd)
		close(fd);
}

bool	take_redirection(t_list *list,
int *read_pipe, int *write_pipe, bool is_child)
{
	int	fd_input;
	int	fd_output;
	int	i;

	fd_input = take_heredoc(list->heredoc, read_pipe);
	fd_output = 0;
	i = 0;
	if (fd_input == -1)
		return (true);
	while (list->redirection[i].content)
	{
		if (!list->heredoc && list->redirection[i].guillemet == '<'
			&& list->redirection[i].is_double == false)
			fd_input = one_redirection(list->redirection[i], read_pipe,
					write_pipe, fd_input);
		if (list->redirection[i].guillemet == '>')
			fd_output = one_redirection(list->redirection[i], read_pipe,
					write_pipe, fd_output);
		if (take_redirection_error(fd_input, fd_output))
			return (true);
		i++;
	}
	take_redirection_dupe(read_pipe, fd_input, 0, is_child);
	take_redirection_dupe(write_pipe, fd_output, 1, is_child);
	return (false);
}
