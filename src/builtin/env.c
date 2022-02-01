/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 11:12:09 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/01 17:51:48 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_error.h"
#include "global.h"
#include <stdlib.h>

int	builtin_env(char **argv, char **env)
{
	if (str_tab_len(argv) != 1)
	{
		minishell_error("env", (char *) NULL, MAXARG);
		return (1);
	}
	print_str_tab(env);
	return (0);
}
