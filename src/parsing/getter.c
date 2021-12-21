/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:01:29 by nfaivre           #+#    #+#             */
/*   Updated: 2021/12/21 15:27:58 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdlib.h>

static char	*get_one_word(char *str)
{
	bool	single_quote;
	bool	double_quote;
	int		i;
	char	*word;

	single_quote = false;
	double_quote = false;
	i = 0;
	str = skip_space(str);
	if (!word_len(str))
		return ((char *) NULL);
	word = (char *)malloc(sizeof(char) * (word_len(str) +1));
	if (!word)
	{
		write(2, "A malloc failed !\n", 18);
		return ((char *) NULL);
	}
	update_cote_status(&single_quote, &double_quote, *str);
	while (*str && ((*str != ';' && *str != '|' && *str != ' ' && *str != '>' && *str != '<') || (single_quote == true || double_quote == true)))
	{
		if (!((*str == '\'' && double_quote == false) || (*str == '"' && single_quote == false)))
		{
			word[i] = *str;
			i++;
		}
		str++;
		update_cote_status(&single_quote, &double_quote, *str);
	}
	word[i] = '\0';
	return (word);
}

char	**get_output_input(char *input, char guillemet)
{
	bool	single_quote;
	bool	double_quote;
	char	**word;

	single_quote = false;
	double_quote = false;
	word = (char **) NULL;
	while (*input)
	{
		update_cote_status(&single_quote, &double_quote, *input);
		while (*input && ((*input != '|' && *input != ';' && *input != guillemet) || (single_quote == true || double_quote == true)))
		{
			input++;
			update_cote_status(&single_quote, &double_quote, *input);
		}
		if (*input == guillemet)
			input++;
		else
			break ;
		if (*input == guillemet)
			input++;
		input = skip_space(input);
		if (!word_len(input))
		{
			write(2, "output vide\n", 12);
			return ((char **) NULL);
		}
		word = add_str_to_str_tab(word, get_one_word(input));
		if (!word)
		{
			write(2, "Malloc failed !\n", 16);
			return ((char **) NULL);
		}
	}
	return (word);
}

char	**get_argv(char *input)
{
	char	**argv;

	argv = (char **) NULL;
	while (*input && *input != '|' && *input != ';')
	{
		input = skip_space(input);
		if (*input == '<' || *input == '>')
		{
			input++;
			if (*input == '<' || *input == '>')
				input++;
			input = skip_space(input);
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
