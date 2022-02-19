/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:51:18 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/19 20:26:57 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "global.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <sys/stat.h>
#include <errno.h>

static int	try_exec(char *executable, t_var *var)
{
	struct stat	stat_executable;

	if (access(executable, X_OK) != -1)
	{
		stat(executable, &stat_executable);
		if (S_ISDIR(stat_executable.st_mode))
		{
			minishell_error(NULL, executable, NOTFILE);
			return (126);
		}
		execve(executable, var->list->argv, *(var->env));
		minishell_error(NULL, executable, UNEXECUTABLE);
		return (126);
	}
	else if (access(executable, F_OK) != -1)
	{
		minishell_error(NULL, executable, RIGHT);
		return (126);
	}
	else
		return (127);
}

int	exec_cmd(t_var *var, char **path)
{
	int		status;	
	char	*executable;

	status = 0;
	if (!path || !var->list->argv[0][0])
	{
		minishell_error(NULL, var->list->argv[0], CMD);
		return (127);
	}
	while (*path && status != 126)
	{
		executable = concat(*path, var->list->argv[0]);
		if (!executable)
		{
			minishell_error("execution (concat)", NULL, ALLOC);
			return (-1);
		}
		status = try_exec(executable, var);
		free(executable);
		path++;
	}
	if (status == 127)
		minishell_error(NULL, var->list->argv[0], CMD);
	return (status);
}

int	exec_file(t_var *var)
{
	int	status;

	status = try_exec(var->list->argv[0], var);
	if (status == 127)
		minishell_error(NULL, var->list->argv[0], INACCESSIBLE);
	return (status);
}
