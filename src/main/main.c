/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:52:55 by nfaivre           #+#    #+#             */
/*   Updated: 2021/12/20 14:24:10 by nfaivre          ###   ########.fr       */
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

static void	print_lists(t_lists *lists)
{
	t_list	*ptr_list;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (lists)
	{
		j = 0;
		ptr_list = lists->list;
		printf("LIST N°%i\n\n\n", i);
		while (lists->list)
		{
			printf("command %i\n\n", j);
			print_tab_str(lists->list->output, "output");
			printf("\n");
			print_tab_str(lists->list->input, "input");
			printf("\n");
			print_tab_str(lists->list->argv, "argv");
			printf("\n\n");
			lists->list = lists->list->next;
			j++;
		}
		lists->list = ptr_list;
		lists = lists->next;
		i++;
	}
}

static void	sig_handler(int sig)
{
	if (sig == SIGINT || sig == SIGQUIT)
		write(1, "\n", 1);
	write(1, PROMPT, 17);
}

static int	parsing(char *input)
{
	t_lists	*lists;
	t_lists	*ptr_lists;
	
	if (*input == 'e' && *(input + 1) == 'x' && *(input + 2) == 'i' && *(input + 3) == 't')
		return (1);
	lists = build_lists(input);
	ptr_lists = lists;
	print_lists(lists);
	free_lists(ptr_lists);
	return (0);
}

int	main(void)
{
	int		parsing_status;
	char	*input;

	parsing_status = 0;
	input = NULL;
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	while (true)
	{
		input = readline(PROMPT);
		parsing_status = parsing(input);
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
