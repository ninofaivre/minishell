/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:09:39 by nfaivre           #+#    #+#             */
/*   Updated: 2022/03/03 21:23:33 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>

#include <fcntl.h>
#include <unistd.h>

static void	sig_handler(int sig)
{
	(void)sig;
}

static char	**init_heredoc(void)
{
	char	**heredoc;

	heredoc = malloc(sizeof(char *));
	if (!heredoc)
		return (NULL);
	heredoc[0] = NULL;
	return (heredoc);
}

static char	**get_one_heredoc(char *eof)
{
	char	**heredoc;
	char	*input;

	signal(SIGINT, &sig_handler);
	rl_catch_signals = 0;
	heredoc = init_heredoc();
	if (!heredoc)
		return (NULL);
	input = readline(">");
	while (!is_same_string(input, eof) && input)
	{
		heredoc = add_str_to_str_tab(heredoc, input);
		if (!heredoc)
		{
			free(input);
			return (NULL);
		}
		input = readline(">");
	}
	if (input)
		free(input);
	return (heredoc);
}

bool	get_heredoc(t_redirection *redirection, char ***heredoc)
{
	*heredoc = NULL;
	while (redirection->content)
	{
		if (redirection->guillemet == '<')
		{
			if (*heredoc)
				free_str_tab(heredoc);
			if (redirection->is_double)
			{
				*heredoc = get_one_heredoc(redirection->content);
				if (!*heredoc)
					return (true);
			}
		}
		redirection++;
	}
	return (false);
}
