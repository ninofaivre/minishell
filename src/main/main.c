/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:52:55 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/20 23:11:17 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "builtin.h"
#include "execution.h"
#include "parsing.h"
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>

int	g_status;

void	echo_ctrl_off(void)
{
	struct termios	tty;

	tcgetattr(0, &tty);
	tty.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &tty);
}

static void	sig_handler(int sig, siginfo_t *info, void *context)
{
	(void)context;
	wait_childs(-100, NULL);
	if (sig == SIGINT)
		g_status = 130;
	if (sig == SIGQUIT && info->si_pid == 0)
		g_status = 131;
	if (sig == SIGINT && info->si_pid != 0)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT && info->si_pid != 0 && RL_READLINE_VERSION == 2049)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	parse_execute(t_var *var, char *input)
{
	int		new_status;

	var->status = g_status;
	var->list = parse(var, input);
	var->ptr_start_list = var->list;
	free(input);
	if (var->list)
	{
		new_status = execution(var);
		if (new_status != -2)
			g_status = new_status;
		free_list(var->list);
		var->list = NULL;
	}
}

static void	init(char **env, struct sigaction *sa, t_var *var)
{
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
}

int	main(int argc, char **argv, char **env)
{
	struct sigaction	sa;
	char				*input;
	t_var				var;

	(void)argc;
	(void)argv;
	input = NULL;
	g_status = 0;
	init(env, &sa, &var);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	while (true)
	{
		input = readline(PROMPT);
		if (!input)
			exit(builtin_exit(&var, g_status, false));
		add_history(input);
		parse_execute(&var, input);
	}
}
