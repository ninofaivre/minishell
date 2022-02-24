/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:51:18 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/24 16:30:29 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <errno.h>

void	pipe_error(char *call, char *arg)
{
	if (errno == EMFILE)
		minishell_error(call, arg, MAXFDPROC);
	else if (errno == ENFILE)
		minishell_error(call, arg, MAXFDSYS);
}

void	close_pipe(int *pipe)
{
	if (pipe)
	{
		close(pipe[0]);
		close(pipe[1]);
	}
}

void	write_str_tab_to_fd(char **str_tab, int fd)
{
	while (*str_tab)
	{
		write(fd, *str_tab, str_len(*str_tab));
		write(fd, "\n", 1);
		str_tab++;
	}
}

int	count_list(t_var *var)
{
	int	n_list;

	n_list = 0;
	while (var->list)
	{
		n_list++;
		var->list = var->list->next;
	}
	var->list = var->ptr_start_list;
	return (n_list);
}
