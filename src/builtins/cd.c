/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 10:19:49 by nfaivre           #+#    #+#             */
/*   Updated: 2022/01/24 15:43:10 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "minishell_error.h"
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

static int	free_update_pwd(char **export_argv, char *export_argv_0,
char *export_argv_1, char *pwd)
{
	int	to_return;

	if (!export_argv || !export_argv_0 || !export_argv_1 || !pwd)
		to_return = -1;
	else
		to_return = 0;
	if (export_argv)
		free_str_tab(export_argv);
	if (export_argv_0)
		free(export_argv_0);
	if (export_argv_1)
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
	export_argv_1 = concat("PATH=\0", pwd);
	if (export_argv && export_argv_0 && export_argv_1 && pwd)
	{
		export_argv[0] = export_argv_0;
		export_argv[1] = export_argv_1;
		export_argv[2] = (char *) NULL;
		ft_export(export_argv, env);
	}
	else
		minishell_error("cd (update_pwd)", ALLOC);
	return (free_update_pwd(export_argv, export_argv_0, export_argv_1, pwd));
}

int	cd(char **argv, char ***env)
{
	if (str_tab_len(argv) > 2)
	{
		minishell_error("cd", MAXARG);
		return (1);
	}
	if (chdir(argv[1]) == -1)
	{
		if (errno == ENOTDIR)
			minishell_error("cd", NOTDIR);
		else
			minishell_error("cd", INACCESSIBLE);
		return (1);
	}
	else
		return (update_pwd(env));
}
