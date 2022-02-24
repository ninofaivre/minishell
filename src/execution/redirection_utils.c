/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 18:26:43 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/24 23:00:44 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <fcntl.h>
#include <stdlib.h>

int	take_heredoc(char **heredoc, int *read_pipe)
{
	int		pipe_tab[2];

	if (!heredoc)
		return (0);
	if (read_pipe)
	{
		close(read_pipe[0]);
		read_pipe = NULL;
	}
	if (pipe(pipe_tab) == -1)
	{
		pipe_error("execution (here-doc)", NULL);
		return (-1);
	}
	write_str_tab_to_fd(heredoc, pipe_tab[1]);
	close(pipe_tab[1]);
	return (pipe_tab[0]);
}

int	take_input(char *content, int fd_input)
{
	int	fd;

	fd = 0;
	if (fd_input)
		close(fd_input);
	if (access(content, R_OK) == -1)
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
