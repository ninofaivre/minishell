/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 16:52:55 by nfaivre           #+#    #+#             */
/*   Updated: 2021/11/24 09:44:30 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

static void	handle_ctrl_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	write(1, PROMPT, 17);
}

static int	parsing(char *input)
{
	return (0);
}

int	main(void)
{
	int		parsing_status;
	char	*input;

	parsing_status = 0;
	input = NULL;
	while (true)
	{
		signal(SIGINT, handle_ctrl_c);
		input = readline(PROMPT);
		parsing_status = parsing(input);
		free(input);
		if (parsing_status)
		{
			if (parsing_status == -1)
				exit(EXIT_FAILURE);
			else if (parsing_status == 1)
				exit(EXIT_SUCCESS);
		}
	}
}
