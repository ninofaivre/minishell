/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 17:17:05 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/22 23:42:30 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execution.h"
#include "builtin.h"
#include <stdlib.h>

int	builtin_main(t_var *var)
{
	if (var->list->redirection[0].content)
		if (take_redirection(var->list, NULL, NULL, false))
			return (EXIT_FAILURE);
	if (is_same_string(var->list->argv[0], "export"))
		return (builtin_export(var->list->argv, var->minishell_env));
	else if (is_same_string(var->list->argv[0], "unset"))
		return (builtin_unset(var->list->argv, var));
	else if (is_same_string(var->list->argv[0], "cd"))
		return (builtin_cd(var->list->argv, var->minishell_env));
	else if (is_same_string(var->list->argv[0], "exit"))
		return (builtin_exit(var, var->status, false));
	return (-1);
}

int	builtin_child(t_var *var)
{
	if (is_same_string(var->list->argv[0], "export"))
		return (builtin_export(var->list->argv, var->minishell_env));
	else if (is_same_string(var->list->argv[0], "unset"))
		return (builtin_unset(var->list->argv, var));
	else if (is_same_string(var->list->argv[0], "cd"))
		return (builtin_cd(var->list->argv, var->minishell_env));
	else if (is_same_string(var->list->argv[0], "exit"))
		return (builtin_exit(var, var->status, true));
	else if (is_same_string(var->list->argv[0], "echo"))
		return (builtin_echo(var->list->argv));
	else if (is_same_string(var->list->argv[0], "pwd"))
		return (builtin_pwd());
	else if (is_same_string(var->list->argv[0], "env"))
		return (builtin_env(var->list->argv, var->minishell_env));
	return (-1);
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
		|| is_same_string(argv[0], "env") || (is_same_string(argv[0], "export")
			&& !argv[1]))
		return (true);
	else
		return (false);
}
