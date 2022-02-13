/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:46:49 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/13 17:37:16 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "builtin.h"
#include <stdlib.h>

static void	cpy_env_in_new_env(char **env, char **new_env, char *name)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[j])
	{
		if (comp_env_var_name(env[j], name))
			free(env[j]);
		else
			new_env[i++] = env[j];
		j++;
	}
	new_env[i] = (char *) NULL;
}

static char	**update_export_history(char *name, char **export_history)
{
	char	**new_export_history;
	int		i;
	int		j;

	if (!exist_in_export_history(export_history, name))
		return (export_history);
	new_export_history = (char **)malloc(sizeof(char *) * (str_tab_len(export_history)));
	i = 0;
	j = 0;
	if (!new_export_history)
		return (NULL);
	while (export_history[i])
	{
		if (comp_export_history_var(export_history[i], name))
			free(export_history[i++]);
		else
		{
			new_export_history[j] = export_history[i];
			j++;
			i++;
		}
	}
	new_export_history[i] = NULL;
	return (new_export_history);
}

static bool	unset_one_var(char *name, char ***env, char ***export_history)
{
	char	**new_env;
	char	**new_export_history;

	new_export_history = update_export_history(name, *export_history);
	if (!new_export_history)
	{
		minishell_error("unset", (char *) NULL, ALLOC);
		return (true);
	}
	if (!search_in_env(name, *env))
		return (false);
	new_env = (char **)malloc(sizeof(char *) * str_tab_len(*env));
	if (!new_env)
	{
		free_str_tab(new_export_history);
		minishell_error("unset", (char *) NULL, ALLOC);
		return (true);
	}
	cpy_env_in_new_env(*env, new_env, name);
	if (*env)
		free(*env);
	*env = new_env;
	if (*export_history)
		free(*export_history);
	*export_history = new_export_history;
	return (false);
}

int	builtin_unset(char **argv, char ***env, char ***export_history)
{
	argv++;
	while (*argv)
		if (unset_one_var(*argv++, env, export_history))
			return (-1);
	return (0);
}
