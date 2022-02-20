/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 10:19:49 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/20 16:01:33 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "minishell_error.h"
#include "builtin.h"
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

static int	free_update_pwd(char **export_argv, char *export_argv_0,
char *export_argv_1, char *pwd)
{
	int	to_return;

	if (!export_argv || !export_argv_0 || !export_argv_1 || !pwd)
	{
		minishell_error("cd (update_pwd)", NULL, ALLOC);
		to_return = -1;
	}
	else
		to_return = 0;
	if (export_argv)
		free_str_tab(&export_argv);
	if (export_argv_0 && to_return == 1)
		free(export_argv_0);
	if (export_argv_1 && to_return == 1)
		free(export_argv_1);
	if (pwd)
		free(pwd);
	return (to_return);
}

static int	update_pwd(t_env *minishell_env)
{
	char	**export_argv;
	char	*export_argv_0;
	char	*export_argv_1;
	char	*pwd;

	export_argv = malloc(sizeof(char *) * 3);
	if (export_argv)
		export_argv[0] = NULL;
	export_argv_0 = str_dupe("export\0");
	pwd = get_pwd();
	export_argv_1 = concat("OLDPWD=\0", get_env_var_value(minishell_env, "PWD"));
	if (export_argv && export_argv_0 && export_argv_1 && pwd)
	{
		export_argv[0] = export_argv_0;
		export_argv[1] = export_argv_1;
		export_argv[2] = NULL;
		builtin_export(export_argv, minishell_env);
		free(export_argv[1]);
		export_argv[1] = concat("PWD=\0", pwd);
		if (export_argv[1])
			builtin_export(export_argv, minishell_env);
	}
	return (free_update_pwd(export_argv, export_argv_0, export_argv_1, pwd));
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
	return (update_pwd(minishell_env));
}
