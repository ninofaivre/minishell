/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 17:53:47 by nfaivre           #+#    #+#             */
/*   Updated: 2022/01/30 19:08:28 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "parsing.h"
#include "execution.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <limits.h>

static int	exit_atoi(char *str)
{
	long long int	nbr;

	nbr = 0;
	while (*str)
	{
		if (!is_charset(*str, "0123456789"))
			return (-2);
		if (((nbr * 10) + (*str - '0')) > LLONG_MAX)
			return (-1);
		nbr = (nbr * 10) + (*str - '0');
		str++;
	}
	return (nbr % 256);
}

void	exit_clean(char **env, t_list *list)
{
	function ((t_var *) NULL, (int *) NULL, (int *) NULL);
	free_str_tab(env);
	free_list(list);
	clear_history();
	rl_clear_history();
}

int	builtin_exit(bool error, char **env, t_list *list, bool child)
{
	int	n_arg;
	int	at_exit;

	if (list)
		n_arg = str_tab_len(list->argv);
	else
		n_arg = 0;
	if (error == true)
		at_exit = EXIT_FAILURE;
	else
		at_exit = EXIT_SUCCESS;
	if (n_arg > 2)
	{
		minishell_error("exit", MAXARG);
		at_exit = 1;
	}
	else if (n_arg == 1)
		at_exit = EXIT_SUCCESS;
	else if (n_arg == 2)
	{
		at_exit = exit_atoi(list->argv[1]);
		if (at_exit < 0)
			at_exit = 2;
		if (at_exit == -1)
			minishell_error("exit", INTTOOHIGH);
		else if (at_exit == -2)
			minishell_error("exit", CHARNOTINT);
	}
	if (child == false)
		exit_clean(env, list);
	if ((child == true || n_arg > 2) && error == false)
		return (at_exit);
	else
		exit(at_exit);
}
