/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 00:01:24 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/25 19:16:41 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include <stdio.h>

bool	is_arg_existing_in_env(t_env *minishell_env, char *arg)
{
	bool	exist;

	if (count_char_in_str(arg, '='))
	{
		arg[str_chr(arg, '=')] = '\0';
		exist = is_existing_in_env(minishell_env, arg);
		arg[str_chr(arg, '\0')] = '=';
	}
	else
		exist = is_existing_in_env(minishell_env, arg);
	return (exist);
}

bool	parse_export_arg(char *arg)
{
	if (!is_env_var_name_allowed(*arg, true))
		return (true);
	while (*arg && *arg != '=')
	{
		if (!is_env_var_name_allowed(*arg, false))
			return (true);
		arg++;
	}
	return (false);
}

void	print_one_export_history(t_env *minishell_env)
{
	if (!minishell_env->name)
		return ;
	printf("declare -x %s", minishell_env->name);
	if (minishell_env->value)
		printf("=\"%s\"", minishell_env->value);
	printf("\n");
}

char	*find_biggest_name(t_env *minishell_env)
{
	char	*biggest_name;
	t_env	*ptr_start_minishell_env;

	ptr_start_minishell_env = minishell_env;
	biggest_name = minishell_env->name;
	while (minishell_env)
	{
		if (str_cmp(minishell_env->name, biggest_name) > 0
			&& !is_same_string(minishell_env->name, "_"))
		{
			biggest_name = minishell_env->name;
			minishell_env = ptr_start_minishell_env;
		}
		else
			minishell_env = minishell_env->next;
	}
	minishell_env = ptr_start_minishell_env;
	return (biggest_name);
}

t_env	*find_lowest_name(t_env *minishell_env, t_env	*old_lowest_name)
{
	t_env	*lowest_name;
	t_env	*ptr_start_minishell_env;

	ptr_start_minishell_env = minishell_env;
	lowest_name = NULL;
	while (minishell_env)
	{
		if ((!lowest_name
				|| str_cmp(minishell_env->name, lowest_name->name) < 0)
			&& (!old_lowest_name
				|| str_cmp(minishell_env->name, old_lowest_name->name) > 0))
		{
			lowest_name = minishell_env;
			minishell_env = ptr_start_minishell_env;
		}
		else
			minishell_env = minishell_env->next;
	}
	minishell_env = ptr_start_minishell_env;
	return (lowest_name);
}
