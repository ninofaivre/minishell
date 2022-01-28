/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:52:55 by nfaivre           #+#    #+#             */
/*   Updated: 2022/01/28 16:31:27 by nfaivre          ###   ########.fr       */
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

static void	print_tab_redirection(t_redirection *redirection)
{
	int	i;

	i = 0;
	if (!redirection)
	{
		printf("list->redirection : (t_redirection *) NULL\n");
		return ;
	}
	while (redirection[i].content)
	{
		if (redirection[i].is_double == true)
			printf("list->redirection[%i] : %c%c%s", i, redirection->guillemet,
					redirection->guillemet, redirection[i].content);
		else
			printf("list->redirection[%i] : %c%s\n", i, redirection->guillemet,
				redirection[i].content);
		i++;
	}
}

static void	print_tab_str(char **tab_str, char *name)
{
	int	i;

	i = 0;
	if (!tab_str)
	{
		printf("%s : (char **) NULL\n", name);
		return ;
	}
	while (tab_str[i])
	{
		printf("%s[%i] : %s\n", name, i, tab_str[i]);
		i++;
	}
}

static void	print_list(t_list *list)
{
	t_list	*ptr_list;
	int		i;

	i = 0;
	ptr_list = list;
	if (!list)
		printf("list : (t_list *) NULL\n");
	while (list)
	{
		printf("list %i\n\n", i);
		print_tab_redirection(list->redirection);
		printf("\n");
		print_tab_str(list->argv, "list->argv");
		printf("\n\n");
		list = list->next;
		i++;
	}
	list = ptr_list;
}

static void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	parsing(char ***env, char *input, int *status)
{
	t_var	var;

	var.status = *status;
	var.env = env;
	var.list = parse(&var, input);
	var.ptr_start_list = var.list;
	print_list(var.list);
	*status = execution(&var);
	free_list(var.list);
}

static void	malloc_env(char ***env)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = (char **)malloc(sizeof(char *) * (str_tab_len(*env) + 1));
	while ((*env)[i])
	{
		new_env[i] = str_dupe((*env)[i]);
		i++;
	}
	new_env[i] = (char *) NULL;
	*env = new_env;
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	int		status;

	printf("PID : %i\n", getpid());
	(void)argc;
	(void)argv;
	input = (char *) NULL;
	status = 0;
	malloc_env(&env);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	while (true)
	{
		input = readline(PROMPT);
		if (!input)
			builtin_exit(false, env);
		add_history(input);
		parsing(&env, input, &status);
		free(input);
	}
}
