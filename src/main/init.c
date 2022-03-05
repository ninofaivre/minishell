/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 23:31:13 by nfaivre           #+#    #+#             */
/*   Updated: 2022/03/05 01:20:48 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <termios.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

static void	echo_ctrl_off(void);
static bool	init_shlvl(t_env *minishell_env);
void		sig_handler(int sig, siginfo_t *info, void *context);

void	init(char **env, struct sigaction *sa, t_var *var)
{
	if (isatty(0))
		echo_ctrl_off();
	sa->sa_flags = SA_SIGINFO;
	sa->sa_sigaction = sig_handler;
	sigemptyset(&sa->sa_mask);
	var->ptr_start_list = NULL;
	var->list = NULL;
	var->minishell_env = get_minishell_env(env);
	if (!var->minishell_env)
	{
		minishell_error("main", "get_env", ALLOC);
		exit(EXIT_FAILURE);
	}
	if (init_shlvl(var->minishell_env))
	{
		free_minishell_env(var->minishell_env);
		minishell_error("main", "init shlvl", ALLOC);
		exit(EXIT_FAILURE);
	}
	if (update_pwd(var->minishell_env, true))
	{
		free_minishell_env(var->minishell_env);
		minishell_error("main", "init PWD", ALLOC);
		exit(EXIT_FAILURE);
	}
}

static void	echo_ctrl_off(void)
{
	struct termios	tty;

	tcgetattr(0, &tty);
	tty.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &tty);
}

static bool	init_shlvl(t_env *minishell_env)
{
	bool	status;
	char	*shlvl_value;

	status = false;
	shlvl_value = itoa(ft_atoi(get_env_var_value(minishell_env, "SHLVL")) + 1);
	if (!shlvl_value)
		return (true);
	if (manual_export("SHLVL", shlvl_value, minishell_env))
		status = true;
	free(shlvl_value);
	return (status);
}
