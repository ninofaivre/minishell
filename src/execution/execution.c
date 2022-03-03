/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:51:18 by nfaivre           #+#    #+#             */
/*   Updated: 2022/03/03 22:08:37 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

static int	**init_pipes(int n_list)
{
	int		**pipes;

	pipes = (int **)malloc(sizeof(int *) * n_list);
	if (!pipes)
	{
		minishell_error("execution (pipes)", NULL, ALLOC);
		return (NULL);
	}
	pipes[--n_list] = NULL;
	while (n_list--)
	{
		pipes[n_list] = malloc(sizeof(int) * 2);
		if (!pipes[n_list] || pipe(pipes[n_list]) == -1)
		{
			if (!pipes[n_list])
				minishell_error("execution (pipes)", NULL, ALLOC);
			else
				pipe_error("execution (pipes)", NULL);
			free_pipes(pipes);
			return (NULL);
		}
	}
	return (pipes);
}

int	wait_childs(int pid, t_var *var)
{
	int	status;
	int	to_return;
	int	wait_status;

	to_return = -2;
	wait_status = 0;
	while (wait_status != -1)
	{
		wait_status = wait(&status);
		if (wait_status == pid)
			to_return = WEXITSTATUS(status);
	}
	if (var && is_builtin(var->ptr_start_list->argv[0])
		&& !need_a_child(var->ptr_start_list->argv)
		&& !var->ptr_start_list->next)
		return (pid);
	else
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

static int	call_childs(t_var *var)
{
	int	pid;
	int	i;

	pid = 0;
	i = 0;
	while (var->list)
	{
		if (i == 0)
		{
			if (!var->list->next)
				pid = call_fork_cmd(var, NULL, NULL);
			else
				pid = call_fork_cmd(var, NULL, var->pipes[i]);
		}
		else if (!var->list->next)
			pid = call_fork_cmd(var, var->pipes[i - 1], NULL);
		else
			pid = call_fork_cmd(var, var->pipes[i - 1], var->pipes[i]);
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
		var->pipes = NULL;
	status = wait_childs(call_childs(var), var);
	call_fork_cmd(NULL, NULL, NULL);
	free_pipes(var->pipes);
	return (status);
}
