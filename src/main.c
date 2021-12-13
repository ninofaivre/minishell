/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:52:55 by nfaivre           #+#    #+#             */
/*   Updated: 2021/12/13 11:28:49 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

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
	int		i;

	i = 0;
	/*
	else if (comp_one_word(get_command(input), "exit") == true)
		return (1);
	*/
	if (*input == 'e' && *(input + 1) == 'x' && *(input + 2) == 'i' && *(input + 3) == 't')
		return (1);
	lists = build_lists(input);
	ptr_lists = lists;
	while (lists)
	{
		lists = lists->next;
		i++;
	}
	if (i)
		printf("Il y a %i lists.\n", i);
	free_lists(ptr_lists);
	/*
	else if (comp_one_word(get_command(input), "pwd") == true)
		return (pwd());
	else if (comp_one_word(get_command(input), "cd") == true)
		return (cd(get_arg(input)));
	else
		command_not_found(get_command(input));
	*/
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
