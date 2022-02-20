/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 13:49:36 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/21 00:42:08 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include <unistd.h>
#include <stdlib.h>

static bool	is_same_name(char *minishell_name, char *name)
{
	while (*minishell_name && *name && *minishell_name == *name)
	{
		minishell_name++;
		name++;
	}
	if (!*minishell_name && (!*name || !is_env_var_name_allowed(*name)))
		return (true);
	else
		return (false);
}

char	*get_env_var_value(t_env *minishell_env, char *name)
{
	char	*value;
	t_env	*ptr_start_minishell_env;

	value = NULL;
	ptr_start_minishell_env = minishell_env;
	while (minishell_env)
	{
		if (is_same_name(minishell_env->name, name))
		{
			value = minishell_env->value;
			break ;
		}
		minishell_env = minishell_env->next;
	}
	minishell_env = ptr_start_minishell_env;
	return (value);
}

bool	is_env_var_name_allowed(char c)
{
	if (!c)
		return (false);
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '_')
		return (true);
	else
		return (false);
}

bool	is_existing_in_env(t_env *minishell_env, char *name)
{
	t_env	*ptr_start_minishell_env;

	ptr_start_minishell_env = minishell_env;
	while (minishell_env)
	{
		if (is_same_string(minishell_env->name, name))
		{
			minishell_env = ptr_start_minishell_env;
			return (true);
		}
		minishell_env = minishell_env->next;
	}
	minishell_env = ptr_start_minishell_env;
	return (false);
}

static int	minishell_env_len(t_env *minishell_env)
{
	int		len;
	t_env	*ptr_start_minishell_env;

	len = 0;
	ptr_start_minishell_env = minishell_env;
	while (minishell_env)
	{
		if (minishell_env->value)
			len++;
		minishell_env = minishell_env->next;
	}
	minishell_env = ptr_start_minishell_env;
	return (len);
}

char	**convert_env_in_str_tab(t_env *minishell_env)
{
	int		i;
	char	**env;
	char	*env_var;
	t_env	*ptr_start_minishell_env;

	i = 0;
	env = NULL;
	ptr_start_minishell_env = minishell_env;
	env = malloc(sizeof(char *) * (minishell_env_len(minishell_env) + 1));
	if (!env)
		return (NULL);
	while (minishell_env)
	{
		env[i] = NULL;
		if (minishell_env->value)
		{
			env_var = concat(minishell_env->name, "=");
			if (!env_var)
				return (free_str_tab(&env));
			env[i] = concat(env_var, minishell_env->value);
			free(env_var);
			if (!env[i])
				return (free_str_tab(&env));
			i++;
		}
		minishell_env = minishell_env->next;
	}
	env[i] = NULL;
	minishell_env = ptr_start_minishell_env;
	return (env);
}
