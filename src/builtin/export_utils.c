/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 23:00:33 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/19 23:13:22 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "builtin.h"
#include <stdlib.h>

void	free_replaced_export(char **export_history, char *argv)
{
	while (*export_history)
	{
		if (comp_export_history_var(*export_history, argv)
			&& count_char_in_str(argv, '='))
		{
			free(*export_history);
			return ;
		}
		export_history++;
	}
}

bool	export_parse(char *str)
{
	if (!str || is_charset(*str, "0123456789="))
	{
		minishell_error("export", str, WRONGENVVAR);
		return (true);
	}
	while (*str && *str != '=')
	{
		if (!is_env_var_name_allowed(*str))
		{
			minishell_error("export", str, WRONGENVVAR);
			return (true);
		}
		str++;
	}
	return (false);
}

bool	add_one_var(char ***env, char *str)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = malloc(sizeof(char *) * (str_tab_len(*env) + 2));
	if (!new_env)
		return (true);
	while ((*env)[i])
	{
		new_env[i] = (*env)[i];
		i++;
	}
	new_env[i] = str;
	new_env[i + 1] = NULL;
	if (*env)
		free(*env);
	*env = new_env;
	return (false);
}
