/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:51:18 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/24 14:56:06 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

static int	try_exec_x_ok(char *executable, t_var *var)
{
	struct stat	stat_executable;
	char		**env;

	stat(executable, &stat_executable);
	if (S_ISDIR(stat_executable.st_mode))
	{
		minishell_error(NULL, executable, NOTFILE);
		return (126);
	}
	env = convert_env_in_str_tab(var->minishell_env);
	if (!env)
	{
		minishell_error("execution", "env", ALLOC);
		return (-1);
	}
	execve(executable, var->list->argv, env);
	free_str_tab(&env);
	minishell_error(NULL, executable, UNEXECUTABLE);
	return (126);
}

static int	try_exec(char *executable, t_var *var)
{
	if (access(executable, X_OK) != -1)
		return (try_exec_x_ok(executable, var));
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

	status = 127;
	if (!path || !var->list->argv[0][0])
	{
		minishell_error(NULL, var->list->argv[0], CMD);
		return (127);
	}
	while (*path && status == 127)
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
