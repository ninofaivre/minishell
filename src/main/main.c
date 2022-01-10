/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:52:55 by nfaivre           #+#    #+#             */
/*   Updated: 2022/01/10 11:56:49 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <signal.h>
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
	if (sig == SIGINT || sig == SIGQUIT)
		write(1, "\n", 1);
	write(1, PROMPT, 17);
}

static int	parsing(char ***env, char *input, int *status)
{
	t_list	*list;

	if (*input == 'e' && *(input + 1) == 'x'
		&& *(input + 2) == 'i' && *(input + 3) == 't')
		return (1);
	list = build_list(*env, input, *status);
	print_list(list);
	*status = execution(list, env);
	free_list(list);
	return (0);
}

static void	malloc_env(char ***env)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = (char **)malloc(sizeof(char *) * (str_tab_len(*env) + 1));
	while ((*env)[i])
		new_env[i] = (*env)[i++];
	new_env[i] = (char *) NULL;
	*env = new_env;
}

int	main(int argc, char **argv, char **env)
{
	int		parsing_status;
	char	*input;
	int status = 0;

	(void)argc;
	(void)argv;
	parsing_status = 0;
	input = NULL;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	while (true)
	{
		input = readline(PROMPT);
		add_history(input);
		parsing_status = parsing(env, input);
		free(input);
		if (parsing_status)
		{
			if (parsing_status == -1)
			{
				write(2, "Error\n", 6);
				exit(EXIT_FAILURE);
			}
			else if (parsing_status == 1)
			{
				free(env);
				clear_history();
				rl_clear_history();
				exit(EXIT_SUCCESS);
			}
		}
	}
}
