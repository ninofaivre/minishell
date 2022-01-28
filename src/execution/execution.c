/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:51:18 by nfaivre           #+#    #+#             */
/*   Updated: 2022/01/28 18:54:07 by nfaivre          ###   ########.fr       */
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

static int	**init_pipes(int n_list)
{
	int		**pipes;

	pipes = (int **)malloc(sizeof(int *) * n_list);
	if (!pipes)
		return ((int **) NULL);
	pipes[--n_list] = (int *) NULL;
	while (n_list--)
	{
		pipes[n_list] = (int *)malloc(sizeof(int) * 2);
		pipe(pipes[n_list]);
	}
	return (pipes);
}

static int	wait_childs(int pid, int n_cmd)
{
	int	status;
	int	child_pid;
	int	to_return;

	to_return = -1;
	while (n_cmd--)
	{
		child_pid = wait(&status);
		if (child_pid == pid)
			to_return = WEXITSTATUS(status);
	}
	return (to_return);
}

static void	free_pipes(int **pipes)
{
	int	i;

	i = 0;
	if (!pipes)
		return ;
	while (pipes[i])
		free(pipes[i++]);
	free(pipes);
}

int	execution(t_var *var)
{
	int		**pipes;
	int		i;
	int		n_list;
	int		pid;
	int		status;

	i = -1;
	n_list = count_list(var);
	if (n_list > 1)
		pipes = init_pipes(n_list);
	pid = 0;
	while (var->list)
	{
		if (i == -1)
		{
			if (n_list == 1)
				function(var, (int *) NULL, (int *) NULL);
			else
				function(var, (int *) NULL, pipes[i + 1]);
		}
		else if (!var->list->next)
			pid = function(var, pipes[i], (int *) NULL);
		else
			function(var, pipes[i], pipes[i + 1]);
		i++;
		var->list = var->list->next;
	}
	status = wait_childs(pid, n_list);
	function ((t_var *) NULL, (int *) NULL, (int *) NULL);
	var->list = var->ptr_start_list;
	free_pipes(pipes);
	return (status);
}
