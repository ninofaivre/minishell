/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:51:18 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/04 19:10:34 by nfaivre          ###   ########.fr       */
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
	{
		minishell_error("execution (pipes)", (char *) NULL, ALLOC);
		return ((int **) NULL);
	}
	pipes[--n_list] = (int *) NULL;
	while (n_list--)
	{
		pipes[n_list] = (int *)malloc(sizeof(int) * 2);
		if (!pipes[n_list] || pipe(pipes[n_list]) == -1)
		{
			if (!pipes[n_list])
				minishell_error("execution (pipes)", (char *) NULL, ALLOC);
			else
				pipe_error("execution (pipes)", (char *) NULL);
			free_pipes(pipes);
			return ((int **) NULL);
		}
	}
	return (pipes);
}

static int	wait_childs(int pid, t_var *var, int n_cmd)
{
	int		status;
	int		to_return;
	bool	is_last_cmd_a_child;

	to_return = -1;
	is_last_cmd_a_child = true;
	while (var->list)
	{
		if (!var->list->next && check_builtin(var) == 0)
			is_last_cmd_a_child = false;
		var->list = var->list->next;
	}
	var->list = var->ptr_start_list;
	while (n_cmd--)
	{
		if (wait(&status) == pid && is_last_cmd_a_child)
			to_return = WEXITSTATUS(status);
	}
	if (is_last_cmd_a_child == false)
		return (pid);
	return (to_return);
}

void	free_pipes(int **pipes)
{
	int	i;

	i = 0;
	if (!pipes)
		return ;
	while (pipes[i])
	{
		close_pipe(pipes[i]);
		free(pipes[i++]);
	}
	free(pipes);
}

int	call_childs(t_var *var, int n_list)
{
	int	pid;
	int	i;

	pid = 0;
	i = 0;
	while (var->list)
	{
		if (i == 0)
		{
			if (n_list == 1)
				pid = function(var, (int *) NULL, (int *) NULL);
			else
				pid = function(var, (int *) NULL, var->pipes[i]);
		}
		else if (!var->list->next)
			pid = function(var, var->pipes[i - 1], (int *) NULL);
		else
			pid = function(var, var->pipes[i - 1], var->pipes[i]);
		i++;
		var->list = var->list->next;
		if (pid == -1)
			break ;
	}
	var->list = var->ptr_start_list;
	return (pid);
}

int	execution(t_var *var)
{
	int		n_list;
	int		status;

	n_list = count_list(var);
	if (n_list > 1)
	{
		var->pipes = init_pipes(n_list);
		if (!var->pipes)
			return (-1);
	}
	else
		var->pipes = (int **) NULL;
	status = wait_childs(call_childs(var, n_list), var,  n_list);
	function ((t_var *) NULL, (int *) NULL, (int *) NULL);
	free_pipes(var->pipes);
	return (status);
}
