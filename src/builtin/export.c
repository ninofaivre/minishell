/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:46:44 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/01 18:17:32 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "builtin.h"
#include <stdlib.h>

static bool	add_one_var(char ***env, char *str)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = (char **)malloc(sizeof(char *) * (str_tab_len(*env) + 2));
	if (!new_env)
		return (true);
	while ((*env)[i])
	{
		new_env[i] = (*env)[i];
		i++;
	}
	new_env[i] = str;
	new_env[i + 1] = (char *) NULL;
	if (*env)
		free(*env);
	*env = new_env;
	return (false);
}

static bool	export_one_var(char *argv, char ***env)
{
	char	**ptr_env_var;
	char	*str;

	ptr_env_var = search_in_env(argv, *env);
	if (ptr_env_var)
	{
		str = str_dupe(argv);
		if (!str)
		{
			minishell_error("export", (char *) NULL, ALLOC);
			return (true);
		}
		free(*ptr_env_var);
		*ptr_env_var = str;
	}
	else
	{
		str = str_dupe(argv);
		if (!str || add_one_var(env, str))
		{
			minishell_error("export", (char *) NULL, ALLOC);
			return (true);
		}
	}
	return (false);
}

static bool	export_parse(char *str)
{
	if (!str || is_charset(*str, "0123456789"))
	{
		minishell_error("export", str, WRONGENVVAR);
		return (true);
	}
	while (*str && *str != '=')
	{
		if (!is_env_var_name_allowed(*str))
		{
			minishell_error("export", str, WRONGENVVAR);
			return (true);
		}
		str++;
	}
	return (false);
}

int	builtin_export(char **argv, char ***env)
{
	int		exit_status;

	exit_status = EXIT_SUCCESS;
	argv++;
	while (*argv)
	{
		if (export_parse(*argv) || !(count_char_in_str(*argv, '=')))
		{
			if (export_parse(*argv))
				exit_status = EXIT_FAILURE;
			argv++;
			continue ;
		}
		if (export_one_var(*argv, env))
			return (EXIT_FAILURE);
		argv++;
	}
	return (exit_status);
}
