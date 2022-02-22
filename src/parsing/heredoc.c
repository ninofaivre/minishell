/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 20:09:39 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/22 23:59:13 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>

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

char	**get_heredoc(t_redirection *redirection)
{
	int		i;
	char	**heredoc;

	i = 0;
	heredoc = NULL;
	while (redirection[i].content)
	{
		if (redirection[i].guillemet == '<')
		{
			if (heredoc)
				free_str_tab(&heredoc);
			if (redirection[i].is_double)
			{
				heredoc = get_one_heredoc(redirection[i].content);
				if (!heredoc)
					return (NULL);
			}
		}
		i++;
	}
	if (heredoc)
		return (heredoc);
	else
		return (init_heredoc());
}
