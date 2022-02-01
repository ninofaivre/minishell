/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:51:18 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/01 19:17:18 by nfaivre          ###   ########.fr       */
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
