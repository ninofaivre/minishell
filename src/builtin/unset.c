/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:46:49 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/19 22:52:15 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "builtin.h"
#include <stdlib.h>
#include <stdio.h>

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
	new_env[i] = NULL;
}

static char	**update_export_history(char *name, char **export_history)
{
	char	**new_export_history;
	int		i;

	new_export_history = malloc(sizeof(char *) * (str_tab_len(export_history)));
	i = 0;
	if (!new_export_history)
		return (NULL);
	while (*export_history)
	{
		if (comp_export_history_var(*export_history, name))
			export_history++;
		else
		{
			new_export_history[i] = *export_history;
			i++;
			export_history++;
		}
	}
	new_export_history[i] = NULL;
	return (new_export_history);
}

static bool	unset_one_var(char *name, char ***env, char ***export_history)
{
	char	**new_env;
	char	**new_export_history;

	new_env = NULL;
	new_export_history = NULL;
	if (exist_in_export_history(*export_history, name))
	{
		new_export_history = update_export_history(name, *export_history);
		if (!new_export_history)
			return (unset_one_var_error(new_env, new_export_history));
	}
	if (search_in_env(name, *env))
	{
		new_env = malloc(sizeof(char *) * str_tab_len(*env));
		if (!new_env)
			return (unset_one_var_error(new_env, new_export_history));
		cpy_env_in_new_env(*env, new_env, name);
		free(*env);
		*env = new_env;
	}
	if (*new_export_history)
		replace_old_export_history(export_history, new_export_history, name);
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
