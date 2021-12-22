/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:52:55 by nfaivre           #+#    #+#             */
/*   Updated: 2021/12/22 18:54:34 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

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
		print_tab_str(list->output, "list->output");
		printf("\n");
		print_tab_str(list->input, "list->input");
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

static int	parsing(char **env, char *input)
{
	t_list	*list;

	if (*input == 'e' && *(input + 1) == 'x'
		&& *(input + 2) == 'i' && *(input + 3) == 't')
		return (1);
	list = build_list(env, input);
	print_list(list);
	free_list(list);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	int		parsing_status;
	char	*input;

	(void)argc;
	(void)argv;
	//printf("test : %s\n", search_env_var(env, "$HOME"));
	parsing_status = 0;
	input = NULL;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	while (true)
	{
		input = readline(PROMPT);
		parsing_status = parsing(env, input);
		free(input);
		if (parsing_status)
		{
			if (parsing_status == -1)
			{
				write(2, "Error\n", 7);
				exit(EXIT_FAILURE);
			}
			else if (parsing_status == 1)
				exit(EXIT_SUCCESS);
		}
	}
}
