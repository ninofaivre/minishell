/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 10:19:49 by nfaivre           #+#    #+#             */
/*   Updated: 2022/03/05 01:13:38 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

bool	update_pwd(t_env *minishell_env, bool init)
{
	bool	status;
	char	*pwd;

	status = false;
	pwd = get_pwd();
	if (!pwd)
	{
		minishell_error("update_pwd", NULL, ALLOC);
		return (true);
	}
	if (get_env_var_value(minishell_env, "PWD") && init == false
		&& manual_export("OLDPWD", \
	get_env_var_value(minishell_env, "PWD"), minishell_env))
	{
		minishell_error("update_pwd", "OLDPWD", ALLOC);
		status = true;
	}
	if (!status && manual_export("PWD", pwd, minishell_env))
	{
		minishell_error("update_pwd", "PWD", ALLOC);
		status = true;
	}
	free(pwd);
	return (status);
}

static int	chdir_error(char *arg)
{
	if (errno == ENOTDIR)
		minishell_error("cd", arg, NOTDIR);
	else
		minishell_error("cd", arg, INACCESSIBLE);
	return (1);
}

int	builtin_cd(char **argv, t_env *minishell_env)
{
	if (str_tab_len(argv) > 2)
	{
		minishell_error("cd", NULL, MAXARG);
		return (1);
	}
	else if (str_tab_len(argv) == 1)
	{
		if (get_env_var_value(minishell_env, "HOME"))
		{
			if (chdir(get_env_var_value(minishell_env, "HOME")) == -1)
				return (chdir_error(get_env_var_value(minishell_env, "HOME")));
		}
		else
		{
			minishell_error("cd", "HOME", UNDEFINED);
			return (1);
		}
	}
	else if (chdir(argv[1]) == -1)
		return (chdir_error(argv[1]));
	return (update_pwd(minishell_env, false));
}
