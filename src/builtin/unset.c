/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:46:49 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/01 18:24:55 by nfaivre          ###   ########.fr       */
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

static bool	unset_one_var(char *name, char ***env)
{
	char	**new_env;

	if (!search_in_env(name, *env))
		return (false);
	new_env = (char **)malloc(sizeof(char *) * str_tab_len(*env));
	if (!new_env)
	{
		minishell_error("unset", (char *) NULL, ALLOC);
		return (true);
	}
	cpy_env_in_new_env(*env, new_env, name);
	if (*env)
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
