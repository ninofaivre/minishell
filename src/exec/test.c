/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:51:18 by nfaivre           #+#    #+#             */
/*   Updated: 2022/01/21 21:47:33 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>

int	function(t_var *var, int *read_pipe, int *write_pipe)
{
	pid_t		pid;
	int			i;
	char		*executable;
	static char	**path;

	pid = 0;
	i = 0;
	if (!path)
		path = ft_split(getenv("PATH"), ':');
	if (!var->list)
	{
		free(path);
		path = (char **) NULL;
		return (0);
	}
	if (is_same_string(var->list->argv[0], "cd")
		|| is_same_string(var->list->argv[0], "export")
		|| is_same_string(var->list->argv[0], "unset"))
		return (builtin(var, read_pipe));
	else if (is_same_string(var->list->argv[0], "echo")
		|| is_same_string(var->list->argv[0], "pwd")
		|| is_same_string(var->list->argv[0], "env"))
		return (test_fork(var, var->list->argv[0], read_pipe, write_pipe));
	if (count_char_in_str(var->list->argv[0], '/'))
	{
		if (access(var->list->argv[0], X_OK) != -1)
			pid = test_fork(var, var->list->argv[0], read_pipe, write_pipe);
		else
			printf("File not found !\n");
	}
	else
	{
		while (path[i])
		{
			executable = concat(path[i], var->list->argv[0]);
			if (access(executable, X_OK) != -1)
			{
				pid = test_fork(var, executable, read_pipe, write_pipe);
				free(executable);
				break ;
			}
			free(executable);
			i++;
		}
		if (!path[i])
			printf("File not found !\n");
	}
	return (pid);
}

int	**init_pipes(t_list *list)
{
	int		n_cmd;
	t_list	*ptr_list;
	int		**pipes;

	n_cmd = 0;
	ptr_list = list;
	while (list)
	{
		list = list->next;
		n_cmd++;
	}
	if (n_cmd == 0)
		return ((int **) NULL);
	pipes = (int **)malloc(sizeof(int *) * n_cmd);
	pipes[--n_cmd] = (int *) NULL;
	while (n_cmd--)
	{
		pipes[n_cmd] = (int *)malloc(sizeof(int) * 2);
		pipe(pipes[n_cmd]);
	}
	list = ptr_list;
	return (pipes);
}

int	wait_function(int pid, int n_cmd)
{
	int	status;
	int	child_pid;
	int	to_return;

	while (n_cmd--)
	{
		child_pid = wait(&status);
		if (child_pid == pid)
			to_return = WEXITSTATUS(status);
	}
	return (to_return);
}

int	execution(t_var *var)
{
	int		**pipes;
	int		i;
	int		pid;
	int		status;

	i = -1;
	pipes = init_pipes(var->list);
	while (var->list)
	{
		if (i == -1)
			function(var, (int *) NULL, pipes[i + 1]);
		else if (!var->list->next)
			pid = function(var, pipes[i], (int *) NULL);
		else
			function(var, pipes[i], pipes[i + 1]);
		i++;
		var->list = var->list->next;
	}
	status = wait_function(pid, ++i);
	function (var, (int *) NULL, (int *) NULL);
	var->list = var->ptr_start_list;
	return (status);
}
