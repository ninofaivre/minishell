/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 20:43:34 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/19 20:49:32 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include <termios.h>
#include <stdlib.h>

void	echo_ctrl_off(void)
{
	struct termios	tty;

	tcgetattr(0, &tty);
	tty.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &tty);
}

bool	malloc_env(char ***env)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = malloc(sizeof(char *) * (str_tab_len(*env) + 1));
	if (!new_env)
		return (true);
	while ((*env)[i])
	{
		new_env[i] = str_dupe((*env)[i]);
		if (!new_env[i])
		{
			free_str_tab(&new_env);
			return (true);
		}
		i++;
	}
	new_env[i] = NULL;
	*env = new_env;
	return (false);
}

char	**init_export_history(char **env)
{
	char	**export_history;
	int		i;

	i = 0;
	export_history = malloc(sizeof(char *) * (str_tab_len(env) + 1));
	if (!export_history)
		return (NULL);
	while (env[i])
	{
		export_history[i] = concat("declare -x ", env[i]);
		if (!export_history[i])
			return (free_str_tab(&export_history));
		i++;
	}
	export_history[i] = NULL;
	str_tab_sort(export_history);
	return (export_history);
}
