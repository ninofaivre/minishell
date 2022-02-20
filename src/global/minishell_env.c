/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 20:43:34 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/20 22:52:08 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include <stdlib.h>

void	init_one_minishell_env(t_env *minishell_env)
{
	minishell_env->name = NULL;
	minishell_env->value = NULL;
	minishell_env->next = NULL;
}

static char	*get_name(char *str)
{
	int		i;
	char	*name;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	name = malloc(sizeof(char) * (i + 1));
	if (!name)
		return (NULL);
	str_ncpy(name, str, i);
	name[i] = '\0';
	return (name);
}

char	*get_value_arg(char *str)
{
	int		i;
	char	*value;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '=')
		i++;
	value = malloc(sizeof(char) * (str_len(&str[i + 1]) + 1));
	if (!value)
		return (NULL);
	str_ncpy(value, &str[i + 1], str_len(&str[i + 1]));
	value[str_len(&str[i + 1])] = '\0';
	return (value);
}

bool	fill_one_minishell_env(t_env *minishell_env, char *str)
{
	int		i;
	char	*name;
	char	*value;

	name = get_name(str);
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

void	free_one_minishell_env(t_env *minishell_env)
{
	if (minishell_env->name)
		free(minishell_env->name);
	if (minishell_env->value)
		free(minishell_env->value);
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
	while (env[1])
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
