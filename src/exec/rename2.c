/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rename2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:51:18 by nfaivre           #+#    #+#             */
/*   Updated: 2022/01/21 21:41:55 by nfaivre          ###   ########.fr       */
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

int	check_builtin(t_var *var)
{
	if (is_same_string(var->list->argv[0], "cd")
		|| is_same_string(var->list->argv[0], "export")
		|| is_same_string(var->list->argv[0], "unset"))
		return (0);
	else if (is_same_string(var->list->argv[0], "echo")
		|| is_same_string(var->list->argv[0], "pwd")
		|| is_same_string(var->list->argv[0], "env"))
		return (1);
	return (-1);
}

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

	if (check_builtin(var) == 0)
		return (builtin(var, read_pipe));
	else if (check_builtin(var) == 1)
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
