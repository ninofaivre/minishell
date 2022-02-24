/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 11:12:09 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/24 14:41:18 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include <stdio.h>

int	builtin_env(char **argv, t_env *minishell_env)
{
	t_env	*ptr_start_minishell_env;

	if (!minishell_env->name)
		return (0);
	ptr_start_minishell_env = minishell_env;
	if (str_tab_len(argv) != 1)
	{
		minishell_error("env", NULL, MAXARG);
		return (1);
	}
	while (minishell_env)
	{
		if (minishell_env->name && minishell_env->value)
		{
			printf("%s=", minishell_env->name);
			printf("%s\n", minishell_env->value);
		}
		minishell_env = minishell_env->next;
	}
	minishell_env = ptr_start_minishell_env;
	return (0);
}
