/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rename1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:51:18 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/01 15:51:23 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "builtin.h"
#include "parsing.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>

static bool	pid_zero(t_redirection *redirection, int *read_pipe, int *write_pipe)
{
	if (read_pipe)
	{
		close(read_pipe[1]);
		dup2(read_pipe[0], 0);
	}
	if (write_pipe)
	{
		close(write_pipe[0]);
		dup2(write_pipe[1], 1);
	}
	if (redirection[0].content)
		return (take_redirection(redirection, read_pipe, write_pipe));
	else
		return (false);
}

static void	clean_fork(char **env, t_list *ptr_start_list, int **pipes)
{
	exit_clean(env, ptr_start_list);
	free_pipes(pipes);
}

pid_t	test_fork(t_var *var, char **path, int *read_pipe, int *write_pipe)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (pid_zero(var->list->redirection, read_pipe, write_pipe))
			status = EXIT_FAILURE;
		else if (!var->list->argv[0])
			status = EXIT_SUCCESS;
		else if (check_builtin(var) == 1)
			status = builtin(var, (int *) NULL);
		else if (count_char_in_str(var->list->argv[0], '/'))
			status = check_file(var);
		else
			status = check_exec(var, path);
		clean_fork(*(var->env), var->ptr_start_list, var->pipes);
		_exit(status);
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
	{
		if (!var->ptr_start_list->next)
			return (builtin_exit(*(var->env), var->ptr_start_list, false));
		else
			return (builtin_exit(*(var->env), var->list, true));
	}
	else if (is_same_string(var->list->argv[0], "echo"))
		return (builtin_echo(var->list->argv));
	else if (is_same_string(var->list->argv[0], "pwd"))
		return (builtin_pwd());
	else if (is_same_string(var->list->argv[0], "env"))
		return (builtin_env(var->list->argv, *(var->env)));
	return (-1);
}
