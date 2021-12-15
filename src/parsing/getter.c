/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:01:29 by nfaivre           #+#    #+#             */
/*   Updated: 2021/12/15 16:07:54 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdlib.h>

static char	*get_one_word(char *input)
{
	int		i;
	char	*word;

	input = skip_space(input);
	i = word_len(input);
	if (!i)
		return ((char *) NULL);
	word = (char *)malloc(sizeof(char) * (i +1));
	if (!word)
	{
		write(2, "A malloc failed !\n", 18);
		return ((char *) NULL);
	}
	word[i] = '\0';
	if (*input == '\'' || *input == '"')
		input++;
	while (i--)
		word[i] = input[i];
	return (word);
}

char	*get_output(char *input)
{
	bool	single_quote;
	bool	double_quote;
	bool	append;

	single_quote = false;
	double_quote = false;
	append = false;
	while (*input && *input != '|' && *input != ';' && (*input != '>' || single_quote == true || double_quote == true))
	{
		input++;
		update_cote_status(&single_quote, &double_quote, *input);
	}
	if (*input == '>')
		input++;
	else
		return (NULL);
	if (*input == '>')
	{
		input++;
		append = true;
	}
	(void)append;
	input = skip_space(input);
	if (!word_len(input))
	{
		write(2, "output vide\n", 12);
		return (NULL);
	}
	return (get_one_word(input));
}