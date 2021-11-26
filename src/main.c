/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:52:55 by nfaivre           #+#    #+#             */
/*   Updated: 2021/11/24 17:03:47 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

static void	sig_handler(int sig)
{
	if (sig == SIGINT)
		write(1, "\n", 1);
	write(1, PROMPT, 17);
	if (sig == SIGQUIT)
		write(1, "pwd", 3);
}

static int	parsing(char *input)
{
	if (!input)
		return (1);
	else if (comp_one_word(get_command(input), "exit") == true)
		return (1);
	else if (comp_one_word(get_command(input), "pwd") == true)
		return (pwd());
	else if (comp_one_word(get_command(input), "cd") == true)
		return (cd(get_arg(input)));
	else
		command_not_found(get_command(input));
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
