/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_minishell_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 20:43:34 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/22 00:11:06 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include <stdlib.h>

bool	fill_one_minishell_env(t_env *minishell_env, char *str)
{
	char	*name;
	char	*value;

	if (!str)
		return (false);
	name = get_name_arg(str);
	if (!name)
		return (true);
	if (!count_char_in_str(str, '='))
	{
		minishell_env->name = name;
		return (false);
	}
	value = get_value_arg(str);
	if (!value)
	{
		free(name);
		return (true);
	}
	minishell_env->name = name;
	minishell_env->value = value;
	return (false);
}

void	*free_minishell_env(t_env *minishell_env)
{
	t_env	*ptr_next_minishell_env;

	while (minishell_env->next)
	{
		ptr_next_minishell_env = minishell_env->next;
		free_one_minishell_env(minishell_env);
		free(minishell_env);
		minishell_env = ptr_next_minishell_env;
	}
	free_one_minishell_env(minishell_env);
	free(minishell_env);
	return (NULL);
}

t_env	*get_minishell_env(char **env)
{
	t_env	*minishell_env;
	t_env	*ptr_start_minishell_env;

	minishell_env = malloc(sizeof(t_env));
	if (!minishell_env)
		return (NULL);
	ptr_start_minishell_env = minishell_env;
	init_one_minishell_env(minishell_env);
	while (*env && env[1])
	{
		if (!fill_one_minishell_env(minishell_env, *env))
			minishell_env->next = malloc(sizeof(t_env));
		if (!minishell_env->next)
			return (free_minishell_env(ptr_start_minishell_env));
		minishell_env = minishell_env->next;
		init_one_minishell_env(minishell_env);
		env++;
	}
	if (fill_one_minishell_env(minishell_env, *env))
		return (free_minishell_env(ptr_start_minishell_env));
	return (ptr_start_minishell_env);
}
