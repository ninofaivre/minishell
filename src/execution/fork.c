/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 13:51:18 by nfaivre           #+#    #+#             */
/*   Updated: 2022/03/03 22:28:20 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "builtin.h"
#include <stdlib.h>

static bool	dup_pipe_redir(t_list *list,
int *read_pipe, int *write_pipe)
{
	if (read_pipe)
		close(read_pipe[1]);
	if (write_pipe)
		close(write_pipe[0]);
	if (list->redirection[0].content)
		return (take_redirection(list, read_pipe, write_pipe, true));
	else
	{
		if (read_pipe)
			dup2(read_pipe[0], 0);
		if (write_pipe)
			dup2(write_pipe[1], 1);
		return (false);
	}
}

static void	clean_fork(t_var *var)
{
	exit_clean(var);
	free_pipes(var->pipes);
}

static void	close_unused_pipes(int **pipes, int *read_pipe, int *write_pipe)
{
	if (!pipes)
		return ;
	while (*pipes)
	{
		if (!((read_pipe && read_pipe[0] == (*pipes)[0])
			|| (write_pipe && write_pipe[1] == (*pipes)[1])))
			close_pipe(*pipes);
		pipes++;
	}
}

pid_t	fork_cmd(t_var *var, char **path, int *read_pipe, int *write_pipe)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		close_unused_pipes(var->pipes, read_pipe, write_pipe);
		if (dup_pipe_redir(var->list, read_pipe, write_pipe))
			status = EXIT_FAILURE;
		else if (!var->list->argv[0])
			status = EXIT_SUCCESS;
		else if (is_builtin(var->list->argv[0]) == true)
			status = builtin_child(var);
		else if (count_char_in_str(var->list->argv[0], '/'))
			status = exec_file(var);
		else
			status = exec_cmd(var, path);
		clean_fork(var);
		_exit(status);
	}
	else
	{
		close_pipe(read_pipe);
		return (pid);
	}
}

int	call_fork_cmd(t_var *var, int *read_pipe, int *write_pipe)
{
	static char	**path;

	if (!var)
	{
		if (path)
		{
			free_str_tab(&path);
			path = NULL;
		}
		return (0);
	}
	if (!path)
		path = ft_split(get_env_var_value(var->minishell_env, "PATH"), ':');
	if (!path && get_env_var_value(var->minishell_env, "PATH"))
	{
		minishell_error("execution (split_path)", NULL, ALLOC);
		return (-1);
	}
	if (is_builtin(var->list->argv[0])
		&& !var->ptr_start_list->next && !need_a_child(var->list->argv))
		return (builtin_main(var));
	else
		return (fork_cmd(var, path, read_pipe, write_pipe));
}
