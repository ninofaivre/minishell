/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:46:44 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/19 20:26:57 by nfaivre          ###   ########.fr       */
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
	new_env = malloc(sizeof(char *) * (str_tab_len(*env) + 2));
	if (!new_env)
		return (true);
	while ((*env)[i])
	{
		new_env[i] = (*env)[i];
		i++;
	}
	new_env[i] = str;
	new_env[i + 1] = NULL;
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
	if (!count_char_in_str(argv, '='))
		return (false);
	if (ptr_env_var)
	{
		str = str_dupe(argv);
		if (!str)
		{
			minishell_error("export", NULL, ALLOC);
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
			minishell_error("export", NULL, ALLOC);
			return (true);
		}
	}
	return (false);
}

static bool	export_parse(char *str)
{
	if (!str || is_charset(*str, "0123456789="))
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

bool	comp_export_history_var(char *str1, char *str2)
{
	str1 += 11;
	while (*str2 && *str2 != '=' && *str1 && *str1 != '=' && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	if ((*str2 == '=' || !*str2) && (*str1 == '=' || !*str1))
		return (true);
	else
		return (false);
}

bool	exist_in_export_history(char **export_history, char *argv)
{
	while (*export_history)
	{
		if (comp_export_history_var(*export_history, argv))
			return (true);
		export_history++;
	}
	return (false);
}

char	**update_export_history(char **export_history, char *argv)
{
	bool	exist;
	char	**new_export_history;
	char	*new_var;
	int		i;

	exist = exist_in_export_history(export_history, argv);
	new_export_history = malloc(sizeof(char *) * (str_tab_len(export_history) + 1 + !exist));
	new_var = NULL;
	i = 0;
	if (!new_export_history)
		return (NULL);
	while (export_history[i])
	{
		new_export_history[i] = NULL;
		if (comp_export_history_var(export_history[i], argv) && count_char_in_str(argv, '='))
		{
			new_var = concat("declare -x ", argv);
			if (!new_var)
			{
				free(new_export_history);
				return (NULL);
			}
			new_export_history[i] = new_var;
		}
		else
			new_export_history[i] = export_history[i];
		i++;
	}
	if (!exist)
		new_export_history[i++] = concat("declare -x ", argv);
	if (!exist && !new_export_history[i - 1])
	{
		free(new_export_history);
		return (NULL);
	}
	new_export_history[i] = NULL;
	return (new_export_history);
}

static void	free_replaced_export(char **export_history, char *argv)
{
	while (*export_history)
	{
		if (comp_export_history_var(*export_history, argv) && count_char_in_str(argv, '='))
		{
			free(*export_history);
			return ;
		}
		export_history++;
	}
}

int	builtin_export(char **argv, char ***env, char ***export_history)
{
	int		exit_status;
	char	**new_export_history;

	exit_status = EXIT_SUCCESS;
	new_export_history = NULL;
	argv++;
	if (!*argv)
		print_str_tab(*export_history);
	while (*argv)
	{
		if (export_parse(*argv))
				exit_status = EXIT_FAILURE;
		else
		{
			if (export_history)
				new_export_history = update_export_history(*export_history, *argv);
			if (export_history && !new_export_history)
			{
				minishell_error("export", "export_history", ALLOC);
				return (EXIT_FAILURE);
			}
			else if (export_one_var(*argv, env))
			{
				free_replaced_export(new_export_history, *argv);
				if (new_export_history)
					free(new_export_history);
				return (EXIT_FAILURE);
			}
			if (export_history)
			{
				free_replaced_export(*export_history, *argv);
				free(*export_history);
				*export_history = new_export_history;
			}
		}
		argv++;
	}
	str_tab_sort(*export_history);
	return (exit_status);
}
