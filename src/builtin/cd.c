/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 10:19:49 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/13 15:37:28 by nfaivre          ###   ########.fr       */
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
		minishell_error("cd (update_pwd)", (char *) NULL, ALLOC);
		to_return = -1;
	}
	else
		to_return = 0;
	if (export_argv)
		free_str_tab(export_argv);
	if (export_argv_0 && to_return == 1)
		free(export_argv_0);
	if (export_argv_1 && to_return == 1)
		free(export_argv_1);
	if (pwd)
		free(pwd);
	return (to_return);
}

static int	update_pwd(char ***env)
{
	char	**export_argv;
	char	*export_argv_0;
	char	*export_argv_1;
	char	*pwd;

	export_argv = (char **)malloc(sizeof(char *) * 3);
	if (export_argv)
		export_argv[0] = (char *) NULL;
	export_argv_0 = str_dupe("export\0");
	pwd = get_pwd();
	export_argv_1 = concat("OLDPWD=\0", env_var_value(*env, "$PWD"));
	if (export_argv && export_argv_0 && export_argv_1 && pwd)
	{
		export_argv[0] = export_argv_0;
		export_argv[1] = export_argv_1;
		export_argv[2] = (char *) NULL;
		builtin_export(export_argv, env, NULL);
		free(export_argv[1]);
		export_argv[1] = concat("PWD=\0", pwd);
		if (export_argv[1])
			builtin_export(export_argv, env, NULL);
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

int	builtin_cd(char **argv, char ***env)
{
	if (str_tab_len(argv) > 2)
	{
		minishell_error("cd", (char *) NULL, MAXARG);
		return (1);
	}
	else if (str_tab_len(argv) == 1)
	{
		if (env_var_value(*env, "$HOME"))
		{
			if (chdir(env_var_value(*env, "$HOME")) == -1)
				return (chdir_error(env_var_value(*env, "$HOME")));
		}
		else
		{
			minishell_error("cd", "HOME", UNDEFINED);
			return (1);
		}
	}
	else if (chdir(argv[1]) == -1)
		return (chdir_error(argv[1]));
	return (update_pwd(env));
}
