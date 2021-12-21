/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:01:29 by nfaivre           #+#    #+#             */
/*   Updated: 2021/12/21 20:17:56 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdlib.h>

static char	*get_one_word(char *str)
{
	t_quote	quote;
	int		i;
	char	*word;

	quote = init_quote();
	i = 0;
	str = skip_space(str);
	if (!word_len(str))
		return ((char *) NULL);
	word = (char *)malloc(sizeof(char) * (word_len(str) + 1));
	if (!word)
		return ((char *) NULL);
	update_cote_status(&quote, *str);
	while (*str && (!is_charset(*str, "| ><") || quote.status == true))
	{
		if (!(*str == '\'' && !quote.double_quote)
			&& !(*str == '"' && !quote.single_quote))
			word[i++] = *str;
		str++;
		update_cote_status(&quote, *str);
	}
	word[i] = '\0';
	return (word);
}

char	**get_output_input(char *input, char guillemet)
{
	char	**word;

	word = (char **) NULL;
	while (*input && *input != '|')
	{
		input = skip_space(input);
		if (*input == guillemet)
		{
			input += 1 + (*(input + 1) == guillemet);
			word = add_str_to_str_tab(word, get_one_word(input));
			input = skip_word(input);
		}
		else
		{
			if (is_charset(*input, "><"))
				input += 1 + (is_charset(*(input + 1), "><"));
			input = skip_word(input);
		}
	}
	return (word);
}

char	**get_argv(char *input)
{
	char	**argv;

	argv = (char **) NULL;
	while (*input && *input != '|')
	{
		input = skip_space(input);
		if (is_charset(*input, "><"))
		{
			input += 1 + is_charset(*(input + 1), "><");
			input = skip_word(input);
		}
		else
		{
			argv = add_str_to_str_tab(argv, get_one_word(input));
			input = skip_word(input);
		}
	}
	return (argv);
}
