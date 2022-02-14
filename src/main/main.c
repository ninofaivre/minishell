/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:52:55 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/14 15:23:02 by nfaivre          ###   ########.fr       */
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

static void	sig_handler(int sig, siginfo_t *info, void *context)
{
	(void)context;
	wait_childs(-100, NULL);
	if (sig == SIGINT)
		g_status = 130;
	if (sig == SIGINT && info->si_pid != 0)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT && info->si_pid != 0)
	{
		g_status= 131;
		rl_on_new_line();
		rl_redisplay();
		write(1, "a", 1);
	}
}

static void	parsing(char ***env, char ***export_history, char *input, int *g_status)
{
	t_var	var;
	int		new_status;

	var.status = *g_status;
	var.env = env;
	var.export_history = export_history;
	var.list = parse(&var, input);
	var.ptr_start_list = var.list;
	free(input);
	if (var.list)
	{
		new_status = execution(&var);
		if (new_status != -2)
			*g_status = new_status;
		free_list(var.list);
	}
}

static bool	malloc_env(char ***env)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = (char **)malloc(sizeof(char *) * (str_tab_len(*env) + 1));
	if (!new_env)
		return (true);
	while ((*env)[i])
	{
		new_env[i] = str_dupe((*env)[i]);
		if (!new_env[i])
		{
			free_str_tab(new_env);
			return (true);
		}
		i++;
	}
	new_env[i] = (char *) NULL;
	*env = new_env;
	return (false);
}

static char **init_export_history(char **env)
{
	char	**export_history;
	int		i;

	i = 0;
	export_history = (char **)malloc(sizeof(char *) * (str_tab_len(env) + 1));
	if (!export_history)
		return (NULL);
	while (env[i])
	{
		export_history[i] = concat("declare -x ", env[i]);
		if (!export_history[i])
			return (free_str_tab(export_history));
		i++;
	}
	export_history[i] = NULL;
	str_tab_sort(export_history);
	return (export_history);
}

static void	echo_ctrl_off(void)
{
	struct termios	tty;

	tcgetattr(0, &tty);
	tty.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &tty);
}

int	main(int argc, char **argv, char **env)
{
	struct sigaction	sa;
	char				*input;
	char				**export_history;
	t_var				var;
	char				*leak = malloc(4);

	(void)leak;
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	echo_ctrl_off();
	printf("PID : %i\n", getpid());
	(void)argc;
	(void)argv;
	input = (char *) NULL;
	g_status = 0;
	export_history = init_export_history(env);
	if (!export_history)
	{
		minishell_error("main", NULL, ALLOC);
		exit(EXIT_FAILURE);
	}
	if (malloc_env(&env))
	{
		free_str_tab(export_history);
		minishell_error("main", NULL, ALLOC);
		exit(EXIT_FAILURE);
	}
	var.env = &env;
	var.export_history = &export_history;
	var.ptr_start_list = NULL;
	var.list = NULL;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
	while (true)
	{
		input = readline(PROMPT);
		if (!input)
			exit(builtin_exit(&var, g_status, false));
		add_history(input);
		parsing(&env, &export_history, input, &g_status);
	}
}
