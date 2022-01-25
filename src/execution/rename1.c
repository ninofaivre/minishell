/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rename1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paboutel <paboutel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:51:18 by nfaivre           #+#    #+#             */
/*   Updated: 2022/01/25 03:20:55 by paboutel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "builtin.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>

void	pid_zero(t_var *var, int *read_pipe, int *write_pipe)
{
	if (read_pipe)
		close(read_pipe[1]);
	if (write_pipe)
		close(write_pipe[0]);
	if (read_pipe)
		dup2(read_pipe[0], 0);
	if (write_pipe)
		dup2(write_pipe[1], 1);
	if (var->list->input[0].content)
		take_input(var->list->input, read_pipe);
	if (var->list->output[0].content)
		take_output(var->list->output, write_pipe);
}

pid_t	test_fork(t_var *var, char *executable, int *read_pipe, int *write_pipe)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
	{
		pid_zero(var, read_pipe, write_pipe);
		if (check_builtin(var) == 1)
			_exit(builtin(var, (int *) NULL));
		execve(executable, var->list->argv, *(var->env));
		_exit(EXIT_FAILURE);
	}
	else
	{
		if (read_pipe)
		{
			close(read_pipe[0]);
			close(read_pipe[1]);
		}
		return (pid);
	}
}

int	builtin(t_var *var, int *read_pipe)
{
	if (read_pipe)
	{
		close(read_pipe[0]);
		close(read_pipe[1]);
	}
	if (is_same_string(var->list->argv[0], "export"))
		return (builtin_export(var->list->argv, var->env));
	else if (is_same_string(var->list->argv[0], "unset"))
		return (builtin_unset(var->list->argv, var->env));
	else if (is_same_string(var->list->argv[0], "cd"))
		return (builtin_cd(var->list->argv, var->env));
	else if (is_same_string(var->list->argv[0], "exit"))
		builtin_exit(false, *(var->env));
	else if (is_same_string(var->list->argv[0], "echo"))
		return (builtin_echo(var->list->argv));
	else if (is_same_string(var->list->argv[0], "pwd"))
		return (builtin_pwd());
	else if (is_same_string(var->list->argv[0], "env"))
		return (builtin_env(var->list->argv, *(var->env)));
	return (-1);
}
