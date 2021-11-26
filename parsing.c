/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nfaivre <nfaivre@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 09:55:48 by nfaivre           #+#    #+#             */
/*   Updated: 2021/11/24 12:31:43 by nfaivre          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

char	*get_command(char *input)
{
	input = skip_whitespace(input);
	if (input && (*input == '<' || *input == '>'))
	{
		input++;
		input = skip_whitespace(input);
		input = skip_word(input);
		input = skip_whitespace(input);
	}
	if (!input)
		return (NULL);
	else
		return (input);
}

char	*get_arg(char *input)
{
	input = get_command(input);
	input = skip_word(input);
	input = skip_whitespace(input);
	if (!input)
		return (NULL);
	else
		return (input);
}
