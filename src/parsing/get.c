/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:01:29 by nfaivre           #+#    #+#             */
/*   Updated: 2022/02/26 10:46:49 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include <stdlib.h>

static void	cpy_word(char *word, char *str, char quote)
{
	while (*str && (!is_charset(*str, "| ><") || quote != '\0'))
	{
		if (!(is_charset(*str, "'\"") && (quote == '\0' || quote == *str)))
			*word++ = *str;
		str++;
		quote = update_quote_status(quote, *str);
	}
	*word = '\0';
}

static char	*get_one_word(char *str)
{
	char	quote;
	char	*word;

	quote = update_quote_status('\0', *str);
	word = malloc(sizeof(char) * (word_len(str) + 1));
	if (!word)
		return (NULL);
	cpy_word(word, str, quote);
	return (word);
}

static int	count_redirection(char *str)
{
	int	n_redirection;

	n_redirection = 0;
	while (*str && *str != '|')
	{
		if (is_charset(*str, "><"))
		{
			n_redirection++;
			str += (is_charset(*str, "><")) + (is_charset(str[1], "><"));
		}
		str = skip_word(str);
	}
	return (n_redirection);
}

t_redirection	*get_redirection(char *input)
{
	int				i;
	t_redirection	*redirection;

	i = 0;
	redirection = malloc(sizeof(t_redirection)
			* (count_redirection(input) + 1));
	if (!redirection)
		return (NULL);
	while (*input && *input != '|')
	{
		input = skip_space(input);
		if (is_charset(*input, "><"))
		{
			redirection[i].is_double = is_charset(input[1], "><");
			redirection[i].guillemet = *input;
			input = skip_space(&input[1 + (is_charset(input[1], "><"))]);
			redirection[i++].content = get_one_word(input);
			if (!redirection[i - 1].content)
				return (free_redirection(redirection));
		}
		input = skip_word(input);
	}
	redirection[i].content = NULL;
	return (redirection);
}

char	**get_argv(char *input)
{
	char	**argv;

	argv = malloc(sizeof(char *) * 1);
	if (!argv)
		return (NULL);
	argv[0] = NULL;
	while (*input && *input != '|')
	{
		input = skip_space(input);
		if (is_charset(*input, "><"))
			input = skip_word(&input[1 + is_charset(input[1], "><")]);
		else
		{
			argv = add_str_to_str_tab(argv, get_one_word(input));
			if (!argv)
				return (NULL);
			input = skip_word(input);
		}
	}
	return (argv);
}
