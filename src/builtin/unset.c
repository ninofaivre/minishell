/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 17:46:49 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/20 23:08:19 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "builtin.h"
#include <stdlib.h>
#include <stdio.h>

static void	unset_one_var(char *name, t_env *minishell_env)
{
	t_env	*ptr_start_minishell_env;
	t_env	*ptr_shunt_minishell_env;

	ptr_start_minishell_env = minishell_env;
	if (is_same_string(minishell_env->name, name))
	{
		ptr_start_minishell_env = minishell_env->next;
		free_one_minishell_env(minishell_env);
		free(minishell_env);
		minishell_env = ptr_start_minishell_env;
		return ;
	}
	while (minishell_env->next)
	{
		if (is_same_string(minishell_env->next->name, name))
		{
			ptr_shunt_minishell_env = minishell_env->next->next;
			free_one_minishell_env(minishell_env->next);
			free(minishell_env->next);
			minishell_env->next = ptr_shunt_minishell_env;
			break ;
		}
		minishell_env = minishell_env->next;
	}
	minishell_env = ptr_start_minishell_env;
}

int	builtin_unset(char **argv, t_env *minishell_env)
{
	argv++;
	while (*argv)
		unset_one_var(*argv++, minishell_env);
	return (0);
}
