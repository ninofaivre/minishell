/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rename2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:51:18 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/15 13:29:56 by nfaivre          ###   ########.fr       */
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

static int	exec_path(t_var *var, char **path)
{
	char	*executable;

	if (!path)
		return (127);
	while (*path)
	{
		executable = concat(*path, var->list->argv[0]);
		if (!executable)
		{
			minishell_error("execution (concat)", (char *) NULL, ALLOC);
			return (-1);
		}
		if (access(executable, X_OK) != -1)
		{
			execve(executable, var->list->argv, *(var->env));
			return (EXIT_FAILURE);
		}
		else if (access(executable, F_OK) == 0)
		{
			free(executable);
			return (126);
		}
		free(executable);
		path++;
	}
	return (127);
}

int	check_exec(t_var *var, char **path)
{
	int		status;

	status = exec_path(var, path);
	if (status == 127)
		minishell_error((char *) NULL, var->list->argv[0], CMD);
	else if (status == 126)
		minishell_error((char *) NULL, var->list->argv[0], INACCESSIBLE);
	return (status);
}

int	check_file(t_var *var)
{
	if (access(var->list->argv[0], X_OK) != -1)
	{
		execve(var->list->argv[0], var->list->argv, *(var->env));
		return (EXIT_FAILURE);
	}
	else
		minishell_error((char *) NULL, var->list->argv[0], INACCESSIBLE);
	return (126 + (access(var->list->argv[0], F_OK) == -1));
}

bool	is_builtin(char *argv_0)
{
	if (is_same_string(argv_0, "exit") || is_same_string(argv_0, "echo")
		|| is_same_string(argv_0, "env") || is_same_string(argv_0, "pwd")
		|| is_same_string(argv_0, "export") || is_same_string(argv_0, "unset")
		|| is_same_string(argv_0, "cd"))
		return (true);
	else
		return (false);
}

bool	need_a_child(char **argv)
{
	if (is_same_string(argv[0], "echo") || is_same_string(argv[0], "pwd")
		|| is_same_string(argv[0], "env") || (is_same_string(argv[0], "export") && !argv[1]))
		return (true);
	else
		return (false);
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
