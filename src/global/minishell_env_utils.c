/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 23:46:25 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/25 19:16:57 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include <stdlib.h>

char	*minishell_env_to_string(t_env *minishell_env)
{
	char	*str_env;

	str_env = malloc(sizeof(char) * \
	(str_len(minishell_env->name) + str_len(minishell_env->value) + 2));
	if (!str_env)
		return (NULL);
	str_ncpy(str_env, minishell_env->name, str_len(minishell_env->name));
	str_env[str_len(minishell_env->name)] = '=';
	str_ncpy(&str_env[str_len(minishell_env->name) + 1], \
	minishell_env->value, str_len(minishell_env->value));
	str_env[str_len(minishell_env->name) + 1 + \
	str_len(minishell_env->value)] = '\0';
	return (str_env);
}

bool	is_same_name(char *minishell_name, char *name)
{
	if (!minishell_name || !name)
		return (false);
	while (*minishell_name && *name && *minishell_name == *name)
	{
		minishell_name++;
		name++;
	}
	if (!*minishell_name && (!*name || !is_env_var_name_allowed(*name, false)))
		return (true);
	else
		return (false);
}
