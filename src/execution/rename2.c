/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rename2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:51:18 by nfaivre           #+#    #+#             */
/*   Updated: 2022/01/28 12:42:52 by nfaivre          ###   ########.fr       */
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

int	check_exec(t_var *var, int *read_pipe, int *write_pipe, char **path)
{
	int		status;
	int		i;
	char	*executable;

	status = 127;
	i = 0;
	while (path[i])
	{
		executable = concat(path[i], var->list->argv[0]);
		if (access(executable, X_OK) != -1)
		{
			status = test_fork(var, executable, read_pipe, write_pipe);
			free(executable);
			break ;
		}
		free(executable);
		i++;
	}
	if (!path[i])
		minishell_error(var->list->argv[0], CMD);
	return (status);
}

int	check_file(t_var *var, int *read_pipe, int *write_pipe)
{
	if (access(var->list->argv[0], X_OK) != -1)
		return (test_fork(var, var->list->argv[0], read_pipe, write_pipe));
	else
		minishell_error(var->list->argv[0], INACCESSIBLE);
	return (127);
}

int	check_builtin(char *str)
{
	if (is_same_string(str, "cd") || is_same_string(str, "export")
		|| is_same_string(str, "unset") || is_same_string(str, "exit"))
		return (0);
	else if (is_same_string(str, "echo") || is_same_string(str, "pwd")
		|| is_same_string(str, "env"))
		return (1);
	return (-1);
}

int	function(t_var *var, int *read_pipe, int *write_pipe)
{
	static char	**path;

	if (!path)
		path = ft_split(env_var_value(*(var->env), "$PATH"), ':');
	if (!var->list)
	{
		free_str_tab(path);
		path = (char **) NULL;
		return (0);
	}
	if (check_builtin(var->list->argv[0]) == 0)
		return (builtin(var, read_pipe));
	else if (check_builtin(var->list->argv[0]) == 1)
		return (test_fork(var, var->list->argv[0], read_pipe, write_pipe));
	if (count_char_in_str(var->list->argv[0], '/'))
		return (check_file(var, read_pipe, write_pipe));
	else
		return (check_exec(var, read_pipe, write_pipe, path));
	return (127);
}
