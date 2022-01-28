/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 17:53:47 by nfaivre           #+#    #+#             */
/*   Updated: 2022/01/28 18:55:38 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "parsing.h"
#include "execution.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

void	builtin_exit(bool error, char **env, t_list *list)
{
	function ((t_var *) NULL, (int *) NULL, (int *) NULL);
	free_str_tab(env);
	free_list(list);
	clear_history();
	rl_clear_history();
	if (error == true)
		exit(EXIT_FAILURE);
	else
		exit(EXIT_SUCCESS);
}
