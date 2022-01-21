/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:51:18 by nfaivre           #+#    #+#             */
/*   Updated: 2022/01/18 15:42:57 by nfaivre          ###   ########.fr       */
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

int	function(t_list *list, char ***env, int *read_pipe, int *write_pipe)
{
	pid_t		pid;
	int			i;
	char		*executable;
	static char	**path;

	pid = 0;
	i = 0;
	if (!path)
		path = ft_split(getenv("PATH"), ':');
	if (!list)
	{
		free(path);
		path = (char **) NULL;
		return (0);
	}
	if (is_same_string(list->argv[0], "cd")
		|| is_same_string(list->argv[0], "export")
		|| is_same_string(list->argv[0], "unset"))
		return (builtin(list, env, read_pipe));
	else if (is_same_string(list->argv[0], "echo")
		|| is_same_string(list->argv[0], "pwd")
		|| is_same_string(list->argv[0], "env"))
		return (test_fork(list, *env, list->argv[0], read_pipe, write_pipe));
	if (count_char_in_str(list->argv[0], '/'))
	{
		if (access(list->argv[0], X_OK) != -1)
			pid = test_fork(list, *env, list->argv[0], read_pipe, write_pipe);
		else
			printf("File not found !\n");
	}
	else
	{
		while (path[i])
		{
			executable = concat(path[i], list->argv[0]);
			if (access(executable, X_OK) != -1)
			{
				pid = test_fork(list, *env, executable, read_pipe, write_pipe);
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

int	execution(t_list *list, char ***env)
{
	int		**pipes;
	t_list	*ptr_list;
	int		i;
	int		pid;
	int		status;

	i = -1;
	pipes = init_pipes(list);
	ptr_list = list;
	while (list)
	{
		if (i == -1)
			function(list, env, (int *) NULL, pipes[i + 1]);
		else if (!list->next)
			pid = function(list, env, pipes[i], (int *) NULL);
		else
			function(list, env, pipes[i], pipes[i + 1]);
		i++;
		list = list->next;
	}
	status = wait_function(pid, ++i);
	function (list, env, (int *) NULL, (int *) NULL);
	list = ptr_list;
	return (status);
}
