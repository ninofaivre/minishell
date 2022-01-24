/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 17:53:47 by nfaivre           #+#    #+#             */
/*   Updated: 2022/01/24 18:00:16 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

void	builtin_exit(bool error, char **env)
{
	free_str_tab(env);
	clear_history();
	rl_clear_history();
	if (error == true)
		exit(EXIT_FAILURE);
	else
		exit(EXIT_SUCCESS);
}
