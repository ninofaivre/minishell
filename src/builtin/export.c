/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:46:44 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/24 14:45:55 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <stdlib.h>

static void	print_export_history(t_env *minishell_env)
{
	t_env	*ptr_printed_minishell_env;

	if (!minishell_env->name)
		return ;
	ptr_printed_minishell_env = find_lowest_name(minishell_env, NULL);
	print_one_export_history(ptr_printed_minishell_env);
	while (!is_same_string(ptr_printed_minishell_env->name, \
	find_biggest_name(minishell_env)))
	{
		ptr_printed_minishell_env = find_lowest_name(minishell_env, \
		ptr_printed_minishell_env);
		print_one_export_history(ptr_printed_minishell_env);
	}
}

static int	export_one(char *arg, t_env *minishell_env)
{
	t_env	*ptr_start_minishell_env;

	if (!minishell_env->name)
		return (fill_one_minishell_env(minishell_env, arg) * -1);
	ptr_start_minishell_env = minishell_env;
	while (minishell_env->next)
		minishell_env = minishell_env->next;
	minishell_env->next = malloc(sizeof(t_env));
	if (!minishell_env->next)
	{
		minishell_env = ptr_start_minishell_env;
		return (-1);
	}
	init_one_minishell_env(minishell_env->next);
	if (fill_one_minishell_env(minishell_env->next, arg))
	{
		free(minishell_env->next);
		minishell_env = ptr_start_minishell_env;
		return (-1);
	}
	minishell_env = ptr_start_minishell_env;
	return (0);
}

static int	replace_one(char *arg, t_env *minishell_env)
{
	t_env	*ptr_start_minishell_env;
	char	*new_value;

	ptr_start_minishell_env = minishell_env;
	if (!count_char_in_str(arg, '='))
		return (0);
	arg[str_chr(arg, '=')] = '\0';
	while (minishell_env && !is_same_string(minishell_env->name, arg))
		minishell_env = minishell_env->next;
	arg[str_chr(arg, '\0')] = '=';
	new_value = get_value_arg(arg);
	if (!new_value)
		return (-1);
	free(minishell_env->value);
	minishell_env->value = new_value;
	minishell_env = ptr_start_minishell_env;
	return (0);
}

bool	manual_export(char *name, char *value, t_env *minishell_env)
{
	bool	status;
	char	*tmp;
	char	*export_arg;

	if (!name || !value)
		return (true);
	tmp = concat(name, "=");
	if (!tmp)
		return (true);
	export_arg = concat(tmp, value);
	if (!export_arg)
	{
		free(tmp);
		return (true);
	}
	if (is_existing_in_env(minishell_env, name))
		status = (replace_one(export_arg, minishell_env) == -1);
	else
		status = (export_one(export_arg, minishell_env) == -1);
	free(tmp);
	free(export_arg);
	return (status);
}

int	builtin_export(char **argv, t_env *minishell_env)
{
	int	status;

	status = 0;
	argv++;
	if (!*argv)
		print_export_history(minishell_env);
	while (*argv)
	{
		if (parse_export_arg(*argv))
		{
			minishell_error("export", *argv, WRONGENVVAR);
			status = 1;
			argv++;
			continue ;
		}
		if (is_arg_existing_in_env(minishell_env, *argv))
			status = replace_one(*argv, minishell_env);
		else
			status = export_one(*argv, minishell_env);
		if (status == -1)
			minishell_error("export", *argv, ALLOC);
		argv++;
	}
	return (status);
}
