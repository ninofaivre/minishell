/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:46:44 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/21 00:09:16 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "builtin.h"
#include <stdlib.h>
#include <stdio.h>

static void	print_one_export_history(t_env *minishell_env)
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
		if (str_cmp(minishell_env->name, biggest_name) > 0 && !is_same_string(minishell_env->name, "_"))
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
		if (( !lowest_name || str_cmp(minishell_env->name, lowest_name->name) < 0) && (!old_lowest_name || str_cmp(minishell_env->name, old_lowest_name->name) > 0))
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

static void	print_export_history(t_env *minishell_env)
{
	t_env	*ptr_printed_minishell_env;

	ptr_printed_minishell_env = find_lowest_name(minishell_env, NULL);
	print_one_export_history(ptr_printed_minishell_env);
	while (!is_same_string(ptr_printed_minishell_env->name, find_biggest_name(minishell_env)))
	{
		ptr_printed_minishell_env = find_lowest_name(minishell_env, ptr_printed_minishell_env);
		print_one_export_history(ptr_printed_minishell_env);
	}
}

static bool parse_export_arg(char *arg)
{
	if (is_charset(*arg, "0123456789"))
		return (true);
	while (*arg && *arg != '=')
	{
		if (!is_env_var_name_allowed(*arg))
			return (true);
		arg++;
	}
	return (false);
}

static int	no_env_export(char *arg, t_env *minishell_env)
{
	if (fill_one_minishell_env(minishell_env, arg))
	{
		minishell_error("export", arg, ALLOC);
		return (-1);
	}
	else
		return (0);
}

static int	export_one(char *arg, t_env *minishell_env)
{
	t_env	*ptr_start_minishell_env;

	if (!minishell_env->name)
		return (no_env_export(arg, minishell_env));
	ptr_start_minishell_env = minishell_env;
	while (minishell_env->next)
		minishell_env = minishell_env->next;
	minishell_env->next = malloc(sizeof(t_env));
	if (!minishell_env->next)
	{
		minishell_error("export", arg, ALLOC);
		minishell_env = ptr_start_minishell_env;
		return (-1);
	}
	init_one_minishell_env(minishell_env->next);
	if (fill_one_minishell_env(minishell_env->next, arg))
	{
		free(minishell_env->next);
		minishell_error("export", arg, ALLOC);
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
	{
		minishell_error("export", arg, ALLOC);
		return (-1);
	}
	free(minishell_env->value);
	minishell_env->value = new_value;
	minishell_env = ptr_start_minishell_env;
	return (0);
}

static bool	is_arg_existing_in_env(t_env *minishell_env, char *arg)
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
			continue ;
		}
		if (is_arg_existing_in_env(minishell_env, *argv))
			status = replace_one(*argv, minishell_env);
		else
			status = export_one(*argv, minishell_env);
		argv++;
	}
	return (status);
}
