/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rename2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:51:18 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/01 15:51:18 by nfaivre          ###   ########.fr       */
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

int	check_exec(t_var *var, char **path)
{
	int		i;
	int		status;
	char	*executable;

	i = 0;
	status = 127;
	while (path[i])
	{
		executable = concat(path[i], var->list->argv[0]);
		if (!executable)
		{
			minishell_error("execution (concat)", ALLOC);
			return (-1);
		}
		if (access(executable, X_OK) != -1)
		{
			execve(executable, var->list->argv, *(var->env));
			return (EXIT_FAILURE);
		}
		else if (access(executable, F_OK) == 0)
			status = 126;
		free(executable);
		if (status == 126)
			break ;
		i++;
	}
	if (status == 127)
		minishell_error(var->list->argv[0], CMD);
	else if (status == 126)
		minishell_error(var->list->argv[0], INACCESSIBLE);
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
		minishell_error(var->list->argv[0], INACCESSIBLE);
	return (126 + (access(var->list->argv[0], F_OK) == -1));
}

int	check_builtin(t_var *var)
{
	if (is_same_string(var->list->argv[0], "exit"))
	{
		if (is_same_string(var->ptr_start_list->argv[0], "exit") && !var->ptr_start_list->next)
			return (0);
		else
			return (1);
	}
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
	static char	**path;

	if (!var)
	{
		if (path)
		{
			free_str_tab(path);
			path = (char **) NULL;
		}
		return (0);
	}
	if (!path)
		path = ft_split(env_var_value(*(var->env), "$PATH"), ':');
	if (!path)
	{
		minishell_error("execution (split_path)", ALLOC);
		return (-1);
	}
	if (check_builtin(var) == 0)
		return (builtin(var, read_pipe));
	else
		return (test_fork(var, path, read_pipe, write_pipe));
}
