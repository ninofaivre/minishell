/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:46:49 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/24 14:47:35 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <stdlib.h>

static void	unset_first_var(t_var *var)
{
	t_env	*ptr_minishell_env;
	t_env	*ptr_new_minishell_env;

	ptr_minishell_env = var->minishell_env;
	if (!ptr_minishell_env->next)
	{
		free_one_minishell_env(ptr_minishell_env);
		init_one_minishell_env(ptr_minishell_env);
		return ;
	}
	ptr_new_minishell_env = var->minishell_env->next;
	free_one_minishell_env(ptr_minishell_env);
	free(ptr_minishell_env);
	var->minishell_env = ptr_new_minishell_env;
}

static void	unset_one_var(char *name, t_var *var)
{
	t_env	*ptr_minishell_env;
	t_env	*ptr_new_minishell_env;

	ptr_minishell_env = var->minishell_env;
	if (is_same_string(var->minishell_env->name, name))
	{
		unset_first_var(var);
		return ;
	}
	while (ptr_minishell_env->next)
	{
		if (is_same_string(ptr_minishell_env->next->name, name))
		{
			ptr_new_minishell_env = ptr_minishell_env->next->next;
			free_one_minishell_env(ptr_minishell_env->next);
			free(ptr_minishell_env->next);
			ptr_minishell_env->next = ptr_new_minishell_env;
			return ;
		}
		ptr_minishell_env = ptr_minishell_env->next;
	}
}

int	builtin_unset(char **argv, t_var *var)
{
	argv++;
	while (*argv)
	{
		unset_one_var(*argv, var);
		argv++;
	}
	return (0);
}
