/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 17:53:47 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/07 15:36:29 by nfaivre          ###   ########.fr       */
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
	bool			is_negative;

	nbr = 0;
	if (*str == '-')
	{
		str++;
		is_negative = true;
	}
	else
		is_negative = false;
	while (*str)
	{
		if (!is_charset(*str, "0123456789"))
			return (-2);
		if (((nbr * 10) + (*str - '0')) > LLONG_MAX)
			return (-1);
		nbr = (nbr * 10) + (*str - '0');
		str++;
	}
	if (is_negative)
		return (256 - (nbr % 256));
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

int	builtin_exit(char **env, t_list *list, int status, bool is_child)
{
	int	n_arg;
	int	at_exit;

	if (list)
		n_arg = str_tab_len(list->argv);
	else
		n_arg = 0;
	at_exit = status;
	if (n_arg > 2)
	{
		minishell_error("exit", (char *) NULL, MAXARG);
		return (1);
	}
	else if (n_arg == 2)
	{
		at_exit = exit_atoi(list->argv[1]);
		if (at_exit == -1)
			minishell_error("exit", list->argv[1], INTTOOHIGH);
		else if (at_exit == -2)
			minishell_error("exit", list->argv[1], CHARNOTINT);
		if (at_exit < 0)
			return (2);
	}
	if (is_child == false)
	{
		exit_clean(env, list);
		exit (at_exit);
	}
	else
		return (at_exit);
}
