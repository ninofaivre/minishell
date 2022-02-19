/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 22:52:09 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/19 22:58:04 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "builtin.h"
#include "minishell_error.h"
#include <stdlib.h>
#include <unistd.h>

static void	free_unseted_export(char **export_history, char *argv)
{
	while (*export_history)
	{
		if (comp_export_history_var(*export_history, argv))
		{
			free(*export_history);
			return ;
		}
		export_history++;
	}
}

bool	unset_one_var_error(char **new_env, char **new_export_history)
{
	minishell_error("unset", NULL, ALLOC);
	if (new_export_history)
		free(new_export_history);
	if (new_env)
		free(new_env);
	return (true);
}

void	replace_old_export_history(char ***export_history,
char **new_export_history, char *name)
{
	free_unseted_export(*export_history, name);
	free(*export_history);
	*export_history = new_export_history;
}
