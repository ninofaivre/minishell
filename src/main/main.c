/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:52:55 by nfaivre           #+#    #+#             */
/*   Updated: 2022/01/24 18:08:13 by nfaivre          ###   ########.fr       */
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

static void	print_tab_redirection(t_redirection *redirection,
char *name, char guillemet)
{
	int	i;

	i = 0;
	if (!redirection)
	{
		printf("%s : (t_redirection *) NULL\n", name);
		return ;
	}
	while (redirection[i].content)
	{
		if (redirection[i].is_double == true)
			printf("%s[%i] : %c%c%s\n", name, i, guillemet,
				guillemet, redirection[i].content);
		else
			printf("%s[%i] : %c%s\n", name, i, guillemet,
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
		print_tab_redirection(list->output, "list->output", '>');
		printf("\n");
		print_tab_redirection(list->input, "list->input", '<');
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

static int	parsing(char ***env, char *input, int *status)
{
	t_var	var;

	var.status = *status;
	var.env = env;
	var.list = build_list(&var, input);
	var.ptr_start_list = var.list;
	print_list(var.list);
	*status = execution(&var);
	free_list(var.list);
	return (0);
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
	printf("PID : %i\n", getpid());
	int		parsing_status;
	char	*input;
	int status = 0;

	(void)argc;
	(void)argv;
	parsing_status = 0;
	input = NULL;
	malloc_env(&env);
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	while (true)
	{
		input = readline(PROMPT);
		if (!input)
			builtin_exit(false, env);
		add_history(input);
		parsing_status = parsing(&env, input, &status);
		free(input);
		if (parsing_status)
		{
			if (parsing_status == -1)
			{
				write(2, "Error\n", 6);
				exit(EXIT_FAILURE);
			}
		}
	}
}
