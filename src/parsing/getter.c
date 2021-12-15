/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 13:01:29 by nfaivre           #+#    #+#             */
/*   Updated: 2021/12/15 13:03:02 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"
#include <stdlib.h>

static char	*get_one_word(char *input)
{
	char	*word;
	int		i;

	input = skip_space(input);
	word = (char *)malloc(sizeof(char) * (word_len(input) +1));
	i = word_len(input);
	if (!word)
	{
		write(2, "A malloc failed !\n", 18);
		return ((char *) NULL);
	}
	word[i] = '\0';
	while (i--)
		word[i] = input[i];
	return (word);
}

char	*get_output(char *input)
{
	bool	simplecote;
	bool	doublecote;
	bool	append;

	simplecote = false;
	doublecote = false;
	append = false;
	while (*input && *input != '|' && *input != ';' && (*input != '>' || simplecote == true || doublecote == true))
	{
		input++;
		update_cote_status(&simplecote, &doublecote, *input);
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
	if (!*input || *input == ';' || *input == '|')
	{
		write(2, "output vide\n", 12);
		return (NULL);
	}
	return (get_one_word(input));
}