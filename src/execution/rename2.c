/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rename2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:51:18 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/19 17:17:54 by nfaivre          ###   ########.fr       */
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
	
	stat(executable, &stat_executable);
	if (S_ISDIR(stat_executable.st_mode))
	{
		free(executable);
		minishell_error(NULL, var->list->argv[0], NOTFILE);
		return (126);
	}
	execve(executable, var->list->argv, *(var->env));
	free(executable);
	minishell_error(NULL, var->list->argv[0], UNEXECUTABLE);
	return (126);
}

int	check_exec(t_var *var, char **path)
{
	char		*executable;

	if (!path || !var->list->argv[0][0])
	{
		minishell_error(NULL, var->list->argv[0], CMD);
		return (127);
	}
	while (*path)
	{
		executable = concat(*path, var->list->argv[0]);
		if (!executable)
		{
			minishell_error("execution (concat)", (char *) NULL, ALLOC);
			return (-1);
		}
		if (access(executable, X_OK) != -1)
			return (try_exec(executable, var));
		else if (access(executable, F_OK) == 0)
		{
			free(executable);
			minishell_error(NULL, var->list->argv[0], RIGHT);
			return (126);
		}
		free(executable);
		path++;
	}
	minishell_error(NULL, var->list->argv[0], CMD);
	return (127);
}

int	check_file(t_var *var)
{
	struct stat	stat_path_executable;

	if (access(var->list->argv[0], X_OK) != -1)
	{
		stat(var->list->argv[0], &stat_path_executable);
		if (S_ISDIR(stat_path_executable.st_mode))
		{
			minishell_error(NULL, var->list->argv[0], NOTFILE);
			return (126);
		}
		execve(var->list->argv[0], var->list->argv, *(var->env));
		minishell_error(NULL, var->list->argv[0], UNEXECUTABLE);
		return (126);
	}
	else
		minishell_error((char *) NULL, var->list->argv[0], RIGHT);
	return (126 + (access(var->list->argv[0], F_OK) == -1));
}

int	function(t_var *var, int *read_pipe, int *write_pipe)
{
	static char	**path;

	if (!var)
	{
		if (path)
		{
			free_str_tab(&path);
			path = (char **) NULL;
		}
		return (0);
	}
	if (!path)
		path = ft_split(env_var_value(*(var->env), "$PATH"), ':');
	if (!path && env_var_value(*(var->env), "$PATH"))
	{
		minishell_error("execution (split_path)", (char *) NULL, ALLOC);
		return (-1);
	}
	if (is_builtin(var->list->argv[0]) && !var->ptr_start_list->next && !need_a_child(var->list->argv))
		return (builtin_main(var));
	else
		return (test_fork(var, path, read_pipe, write_pipe));
}
