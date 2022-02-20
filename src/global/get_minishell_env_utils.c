/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_minishell_env_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 23:32:26 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/20 23:34:27 by nfaivre          ###   ########.fr       */
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

char	*get_name_arg(char *str)
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

void	free_one_minishell_env(t_env *minishell_env)
{
	if (minishell_env->name)
		free(minishell_env->name);
	if (minishell_env->value)
		free(minishell_env->value);
}
