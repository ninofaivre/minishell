/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 11:12:09 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/01 17:08:08 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_error.h"
#include "global.h"
#include <stdlib.h>

int	builtin_env(char **argv, char **env)
{
	if (str_tab_len(argv) != 1)
	{
		minishell_error("env", (char *) NULL, MAXARG);
		return (1);
	}
	print_str_tab(env);
	return (0);
}

static bool	comp_env_var_name(char *env_var, char *name)
{
	while (*env_var && *name && *env_var == *name)
	{
		env_var++;
		name++;
	}
	if (*env_var == '=' && !*name)
		return (true);
	else
		return (false);
}

static char	**search_in_env(char *name, char **env)
{
	int	i;

	while (*env)
	{
		i = 0;
		while ((*env)[i] == name[i] && (*env)[i] && name[i] && name[i] != '=')
			i++;
		if ((!name[i] || name[i] == '=') && (*env)[i] == '=')
			return (&(*env));
		env++;
	}
	return ((char **) NULL);
}

static bool	unset_one_var(char *name, char ***env)
{
	int		i;
	int		j;
	char	**new_env;

	i = 0;
	j = 0;
	if (!search_in_env(name, *env))
		return (false);
	new_env = (char **)malloc(sizeof(char *) * str_tab_len(*env));
	if (!new_env)
	{
		minishell_error("unset", (char *) NULL, ALLOC);
		return (true);
	}
	while ((*env)[j])
	{
		if (comp_env_var_name((*env)[j], name))
			free((*env)[j]);
		else
			new_env[i++] = (*env)[j];
		j++;
	}
	new_env[i] = (char *) NULL;
	free(*env);
	*env = new_env;
	return (false);
}

int	builtin_unset(char **argv, char ***env)
{
	argv++;
	while (*argv)
		if (unset_one_var(*argv++, env))
			return (-1);
	return (0);
}

bool	add_one_var(char ***env, char *str)
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
	char	*str;
	char	**ptr_env_var;
	int		exit_status;

	str = (char *) NULL;
	exit_status = EXIT_SUCCESS;
	argv++;
	while (*argv)
	{
		ptr_env_var = (char **) NULL;
		if (export_parse(*argv))
		{
			exit_status = EXIT_FAILURE;
			argv++;
			continue ;
		}
		else
			exit_status = EXIT_SUCCESS;
		if (!(count_char_in_str(*argv, '=')))
		{
			argv++;
			continue ;
		}
		ptr_env_var = search_in_env(*argv, *env);
		if (ptr_env_var)
		{
			str = str_dupe(*argv);
			if (!str)
			{
				minishell_error("export", (char *) NULL, ALLOC);
				return (-1);
			}
			free(*ptr_env_var);
			*ptr_env_var = str;
		}
		else
		{
			str = str_dupe(*argv);
			if (!str || add_one_var(env, str))
			{
				minishell_error("export", (char *) NULL, ALLOC);
				return (-1);
			}
		}
		argv++;
	}
	return (exit_status);
}
